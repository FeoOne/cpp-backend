/**
 * @file tcp_service.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "context/io/io_loop.h"
#include "context/io/connection/tcp_connection.h"
#include "context/io/service/connection_service.h"
#include "context/io/service/request_processing_service.h"

#include "context/io/service/tcp_service.h"

#define RECONNECT_TIMER_DELAY    3000

namespace rocket {

    tcp_service::tcp_service(const groot::setting& config,
                             task_router *router,
                             const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _local_connections {},
            _disconnected_connections {},
            _reconnect_timer { timer::make_unique() },
            _start_callbacks {
                {
                    { connection_kind::master,
                      std::bind(&tcp_service::start_local_master, this, std::placeholders::_1) },
                    { connection_kind::slave,
                      std::bind(&tcp_service::start_local_slave, this, std::placeholders::_1) },
                }
            }
    {
    }

    void tcp_service::setup() noexcept
    {
        _reconnect_timer->setup(delegate()->loop<io_loop>()->loop(),
                                RECONNECT_TIMER_DELAY,
                                RECONNECT_TIMER_DELAY,
                                std::bind(&tcp_service::on_reconnect_timer, this));

        start_local_connections();
    }

    void tcp_service::reset() noexcept
    {
        // todo: release resources
    }

    void tcp_service::register_local_connection(tcp_connection *connection) noexcept
    {
        _local_connections.push_back(connection);
    }

    void tcp_service::start_local_connections() noexcept
    {
        for (auto connection: _local_connections) {
            _start_callbacks.at(connection->kind())(connection);
        }
    }

    void tcp_service::start_local_master(tcp_connection *connection) noexcept
    {
        connection->open(delegate()->loop<io_loop>()->loop(), this);
        // [status] connecting local master
        change_connection_status(connection, connection_status::connecting);

        if (connection->bind() && connection->listen(&tcp_service::connection_callback)) {
            lognotice("Successfully started server socket cid: %llu.", connection->id());
            connection->set_nodelay(true);
            connection->set_nonblock(true);
            connection->set_keepalive(true);
            // [status] local master connected
            change_connection_status(connection, connection_status::connected);
        } else {
            logerror("Failed to start master socket cid: %llu.", connection->id());
            // [status] local master disconnected
            change_connection_status(connection, connection_status::disconnected);
        }
    }

    void tcp_service::start_local_slave(tcp_connection *connection) noexcept
    {
        connection->open(delegate()->loop<io_loop>()->loop(), this);
        // [status] local slave connecting
        change_connection_status(connection, connection_status::connecting);

        auto request { connection->connect(&tcp_service::connect_callback) };
        if (request != nullptr) {
            lognotice("Try to connect cid: %llu.", connection->id());

            connection->set_nodelay(true);
            connection->set_nonblock(true);
        } else {
            logerror("Failed to connect cid: %llu.", connection->id());
            // [status] local slave disconnected
            change_connection_status(connection, connection_status::disconnected);
        }
    }

    void tcp_service::on_reconnect_timer() noexcept
    {
        for (auto connection: _disconnected_connections) {
            _start_callbacks.at(connection->kind())(connection);
        }
    }

    void tcp_service::change_connection_status(tcp_connection *connection, connection_status status) noexcept
    {
        // change status lol
        connection->status(status);
        // produce task about changing connection status
        router()->enqueue(basic_task::create<connection_status_changed_task>(connection->link(), status));

        // reconnect if disconnected connection is local
        if (status == connection_status::disconnected && connection->side() == connection_side::local) {
            auto it { std::find(_disconnected_connections.begin(), _disconnected_connections.end(), connection) };
            if (it == _disconnected_connections.end()) {
                lognotice("Added connection cid %llu to reconnect stack.", connection->id());
                _disconnected_connections.push_back(connection);
                if (_disconnected_connections.size() == 1) {
                    _reconnect_timer->start();
                }
            }
        }
    }

    void tcp_service::reconnection_cleanup(tcp_connection *connection) noexcept
    {
        if (_disconnected_connections.empty()) {
            return;
        }

        _disconnected_connections.remove_if([connection](tcp_connection *another_connection) {
            return connection->id() == another_connection->id();
        });

        if (_disconnected_connections.empty()) {
            _reconnect_timer->stop();
        }
    }

    /**
     * Callback definitions.
     */

    void tcp_service::on_connection(network_handle *handle, int status) noexcept
    {
        auto manager { delegate()->service<connection_service>()->manager<tcp_connection>() };
        auto server_connection { manager->get(handle) };

        if (server_connection == nullptr) {
            logerror("Can't accept connection from unmanaged connection.");
            // component error
            return;
        }

        if (status != 0) {
            logerror("Failed to accept new connection on cid: %llu, %s (%s).",
                     server_connection->id(),
                     uv_strerror(status),
                     uv_err_name(status));
            return;
        }

        // [manager] produce remote connection
        auto client_connection { manager->produce() };
        client_connection->setup(server_connection);
        client_connection->open(delegate()->loop<io_loop>()->loop(), this);

        // [status] connecting remote slave
        change_connection_status(client_connection, connection_status::connecting);

        if (server_connection->accept(client_connection)) {
            lognotice("Accepted new connection with id: %llu.", client_connection->id());

            client_connection->set_nodelay(true);
            client_connection->set_nonblock(true);

            if (!client_connection->start(&tcp_service::alloc_callback, &tcp_service::read_callback)) {
                logerror("Failed to start read connection with id: %llu.", client_connection->id());
                // [status] disconnecting remote slave
                change_connection_status(client_connection, connection_status::disconnecting);
                // connection already accepted, so we must shutdown
                client_connection->shutdown(&tcp_service::shutdown_callback);
            } else {
                // [status] remote slave connected
                change_connection_status(client_connection, connection_status::connected);
            }
        } else {
            logerror("Failed to accept connection.");
            // [status] remote slave disconnected
            change_connection_status(client_connection, connection_status::disconnected);
        }
    }

    void tcp_service::on_connect(uv_request *request, int status) noexcept
    {
        auto handle { reinterpret_cast<network_handle *>(request->connect.handle) };
        auto manager { delegate()->service<connection_service>()->manager<tcp_connection>() };
        auto connection { manager->get(handle) };

        if (connection == nullptr) {
            logerror("Can't connect unmanaged connection.");
            // component error
            return;
        }

        if (status != 0) {
            logerror("Failed to connect cid: %llu, %s (%s).",
                     connection->id(),
                     uv_strerror(status),
                     uv_err_name(status));
            // [status] local slave disconnected
            change_connection_status(connection, connection_status::disconnected);
            return;
        }

        lognotice("Successfully connected id: %llu.", connection->id());

        if (!connection->start(&tcp_service::alloc_callback, &tcp_service::read_callback)) {
            logerror("Cant start connection cid: %llu.", connection->id());
            // [status] disconnecting local slave
            change_connection_status(connection, connection_status::disconnecting);
            connection->shutdown(&tcp_service::shutdown_callback);
            return;
        }

        // local slave connected
        change_connection_status(connection, connection_status::connected);

        reconnection_cleanup(connection);
    }

    void tcp_service::on_alloc(network_handle *handle, size_t, uv_buf_t *buffer) noexcept
    {
        auto manager { delegate()->service<connection_service>()->manager<tcp_connection>() };
        auto connection { manager->get(handle) };

        if (connection == nullptr) {
            logerror("Failed to alloc: connection not found.");
            // component error
            return;
        }

        auto read_stream { connection->read_stream() };

        read_stream->grow_if_needed(); // todo: security issue. add size check to prevent unexpected growing

        buffer->base = reinterpret_cast<char *>(read_stream->tail());
        buffer->len = read_stream->free_size();
    }

    void tcp_service::on_read(network_handle *handle, ssize_t nread, const uv_buf_t *) noexcept
    {
        auto manager { delegate()->service<connection_service>()->manager<tcp_connection>() };
        auto connection { manager->get(handle) };

        if (connection == nullptr) {
            logerror("Failed to read: connection not found.");
            // component error
            return;
        }

        if (nread < 0) {
            // socket fatal error
            auto status { static_cast<int>(nread) };
            logerror("Read error: %s (%s).", uv_strerror(status), uv_err_name(status));
            // [status] disconnecting
            change_connection_status(connection, connection_status::disconnecting);
            connection->shutdown(&tcp_service::shutdown_callback);
            return;
        }

        if (nread > 0) {
            connection->read_stream()->increase_tail(static_cast<size_t>(nread));
            // [io] process input
            delegate()->service<request_processing_service>()->process_input(connection);
        }
    }

    void tcp_service::on_write(uv_request *request, int status) noexcept
    {
        auto handle { reinterpret_cast<network_handle *>(request->connect.handle) };
        auto manager { delegate()->service<connection_service>()->manager<tcp_connection>() };
        auto connection { manager->get(handle) };

        if (connection == nullptr) {
            logerror("Failed to write: connection not found.");
            // component error
            return;
        }

        if (status != 0) {
            logerror("Failed to write cid: %llu, %s (%s).",
                     connection->id(),
                     uv_strerror(status),
                     uv_err_name(status));
            // [status] disconnecting
            change_connection_status(connection, connection_status::disconnecting);
            connection->shutdown(&tcp_service::shutdown_callback);
            return;
        }

        // [io] write output
        // todo: write
    }

    void tcp_service::on_shutdown(uv_request *request, int status) noexcept
    {
        auto handle { reinterpret_cast<network_handle *>(request->connect.handle) };
        auto manager { delegate()->service<connection_service>()->manager<tcp_connection>() };
        auto connection { manager->get(handle) };

        if (connection == nullptr) {
            logerror("Failed to shutdown: connection not found.");
            // component error
            return;
        }

        if (status != 0) {
            logerror("Failed to shutdown cid: %llu, %s (%s).",
                     connection->id(),
                     uv_strerror(status),
                     uv_err_name(status));
            // try one more time
            // todo: maybe better to re-shutdown after some delay by timer
            connection->shutdown(&tcp_service::shutdown_callback);
            return;
        }

        // [status] disconnected
        change_connection_status(connection, connection_status::disconnected);

        if (connection->side() == connection_side::remote) {
            // might to close remote connections
            connection->close(&tcp_service::close_callback);
        }
    }

    void tcp_service::on_close(network_handle *handle) noexcept
    {
        auto manager { delegate()->service<connection_service>()->manager<tcp_connection>() };
        auto connection { manager->get(handle) };

        if (connection == nullptr) {
            logerror("Failed to close: connection not found.");
            // component error
            return;
        }

        // [manager] consume remote connection
        manager->consume(connection);
    }

    /**
     * Callback static wrappers.
     */

    // static
    void tcp_service::connection_callback(uv_stream_t *stream, int status) noexcept
    {
        auto handle { reinterpret_cast<network_handle *>(stream) };
        if (handle != nullptr) {
            auto data { uv_handle_get_data(&handle->handle) };
            if (data != nullptr) {
                reinterpret_cast<tcp_service *>(data)->on_connection(handle, status);
                return;
            }
        }

        logerror("Failed process new connection: %s (%s).", uv_strerror(status), uv_err_name(status));
    }

    // static
    void tcp_service::connect_callback(uv_connect_t *req, int status) noexcept
    {
        auto request { reinterpret_cast<uv_request *>(req) };
        if (request != nullptr) {
            auto data { uv_req_get_data(&request->req) };
            if (data != nullptr) {
                reinterpret_cast<tcp_service *>(data)->on_connect(request, status);
                return;
            }
        }

        logerror("Failed to process connect: %s (%s).", uv_strerror(status), uv_err_name(status));
    }

    // static
    void tcp_service::alloc_callback(uv_handle_t *stream, size_t suggested_size, uv_buf_t *buffer) noexcept
    {
        auto handle { reinterpret_cast<network_handle *>(stream) };
        if (handle != nullptr) {
            auto data { uv_handle_get_data(&handle->handle) };
            if (data != nullptr) {
                static_cast<tcp_service *>(data)->on_alloc(handle, suggested_size, buffer);
                return;
            }
        }

        logerror("Failed to process alloc callback.");
    }

    // static
    void tcp_service::read_callback(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buffer) noexcept
    {
        auto handle { reinterpret_cast<network_handle *>(stream) };
        if (handle != nullptr) {
            auto data { uv_handle_get_data(&handle->handle) };
            if (data != nullptr) {
                static_cast<tcp_service *>(data)->on_read(handle, nread, buffer);
                return;
            }
        }

        logerror("Failed to process read callback.");
    }

    // static
    void tcp_service::write_callback(uv_write_t *req, int status) noexcept
    {
        auto request { reinterpret_cast<uv_request *>(req) };
        if (request != nullptr) {
            auto data { uv_req_get_data(&request->req) };
            if (data != nullptr) {
                static_cast<tcp_service *>(data)->on_write(request, status);
                return;
            }
        }

        logerror("Failed to process write callback: %s (%s).", uv_strerror(status), uv_err_name(status));
    }

    // static
    void tcp_service::shutdown_callback(uv_shutdown_t *req, int status) noexcept
    {
        auto request { reinterpret_cast<uv_request *>(req) };
        if (request != nullptr) {
            auto data { uv_req_get_data(&request->req) };
            if (data != nullptr) {
                static_cast<tcp_service *>(data)->on_shutdown(request, status);
                return;
            }
        }

        logerror("Failed to shutdown connection: %s (%s).", uv_strerror(status), uv_err_name(status));
    }

    // static
    void tcp_service::close_callback(uv_handle_t *stream) noexcept
    {
        auto handle { reinterpret_cast<network_handle *>(stream) };
        if (handle != nullptr) {
            auto data { uv_handle_get_data(&handle->handle) };
            if (data != nullptr) {
                static_cast<tcp_service *>(data)->on_close(handle);
                return;
            }
        }

        logerror("Failed to process close callback.");
    }

}

#undef RECONNECT_TIMER_DELAY
