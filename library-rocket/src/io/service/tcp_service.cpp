/**
 * @file tcp_service.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "io/io_loop.h"
#include "io/connection/tcp_connection.h"
#include "io/task/new_connection_task.h"
#include "io/task/close_connection_task.h"

#include "io/service/tcp_service.h"

#define shutdown_connection(connection) \
    connection->shutdown(&tcp_service::shutdown_routine)

#define start_connection(connection)    \
    connection->start(&tcp_service::alloc_routine, &tcp_service::read_routine)

namespace rocket {

    tcp_service::tcp_service(const groot::setting& config,
                             task_router *router,
                             const work_service_delegate *service_delegate) noexcept :
            crucial(config, router, service_delegate),
            _loop { nullptr },
            _connections { tcp_connection_manager::make_unique() }
    {
    }

    // virtual
    tcp_service::~tcp_service()
    {
    }

    void tcp_service::setup() noexcept
    {
        _loop = delegate()->get_loop<io_loop>()->get_loop();

        setup_servers();
        setup_clients();
    }

    void tcp_service::reset() noexcept
    {
        // _connections->reset();

        _loop = nullptr;
    }

    void tcp_service::listen(const groot::endpoint::sptr& endpoint,
                             u16 backlog,
                             u32 keepalive) noexcept
    {
        auto connection {
                _connections->acquire(endpoint->get_version(), connection::side::LOCAL, connection::kind::SERVER)
        };
        connection->init(_loop, this);

        groot::socket_address addr {};
        setup_sockaddr(endpoint, &addr);

        if (connection->bind(&addr) && connection->listen(backlog, &tcp_service::connection_routine)) {
            lognotice("Successfully started server socket %s:%u.", endpoint->get_host().data(), endpoint->get_port());
            connection->set_nodelay(true);
            connection->set_nonblock(true);
            connection->set_keepalive(true, keepalive);
        } else {
            logerror("Failed to start server socket %s:%u.", endpoint->get_host().data(), endpoint->get_port());
            _connections->release(connection);
        }
    }

    void tcp_service::connect(const groot::endpoint::sptr& endpoint) noexcept
    {
        auto connection {
                _connections->acquire(endpoint->get_version(), connection::side::LOCAL, connection::kind::CLIENT)
        };
        connection->init(_loop, this);

        groot::socket_address addr {};
        setup_sockaddr(endpoint, &addr);

        auto request = connection->connect(&addr, &tcp_service::connect_routine);
        if (request != nullptr) {
            lognotice("Connecting to %s:%u. Connection: 0x%" PRIxPTR ".",
                      endpoint->get_host().data(),
                      endpoint->get_port(),
                      connection);
            connection->set_nodelay(true);
            connection->set_nonblock(true);
        } else {
            logerror("Failed to connect to %s:%u.", endpoint->get_host().data(), endpoint->get_port());
            _connections->release(connection);
        }
    }

    void tcp_service::setup_sockaddr(const groot::endpoint::sptr& endpoint, groot::socket_address *addr) noexcept
    {
        switch (endpoint->get_version()) {
            case groot::ip_version::IPV4: {
                uv_ip4_addr(endpoint->get_host().data(), endpoint->get_port(), &addr->sin);
                break;
            }
            case groot::ip_version::IPV6: {
                uv_ip6_addr(endpoint->get_host().data(), endpoint->get_port(), &addr->sin6);
                break;
            }
        }
    }

    void tcp_service::setup_servers() noexcept
    {
        auto servers_config { get_config()[consts::config::key::SERVERS] };

        if (servers_config.is_null()) {
            return;
        }

        for (size_t i = 0; i < servers_config.size(); ++i) {
            auto server_config { servers_config[i] };

            // skip all except tcp
            if (server_config[consts::config::key::TYPE].to_string() != consts::config::io::TCP) {
                continue;
            }

            // todo: implement ipv6
            auto endpoint {
                    groot::endpoint::ipv4_endpoint(server_config[consts::config::key::HOST].to_string(),
                                                   server_config[consts::config::key::PORT].to_int32<u16>())
            };
            auto backlog { server_config[consts::config::key::BACKLOG].to_int32<u16>() };
            auto keepalive { server_config[consts::config::key::KEEPALIVE].to_int32<u32>() };

            listen(endpoint, backlog, keepalive);
        }
    }

    void tcp_service::setup_clients() noexcept
    {
        auto clients_config { get_config()[consts::config::key::CLIENTS] };

        if (clients_config.is_null()) {
            return;
        }

        for (size_t i = 0; i < clients_config.size(); ++i) {
            auto client_config { clients_config[i] };

            // skip all except tcp
            if (client_config[consts::config::key::TYPE].to_string() != consts::config::io::TCP) {
                continue;
            }

            // todo: implement ipv6
            auto endpoint {
                    groot::endpoint::ipv4_endpoint(client_config[consts::config::key::HOST].to_string(),
                                                   client_config[consts::config::key::PORT].to_int32<u16>())
            };

            connect(endpoint);
        }
    }

    void tcp_service::on_connection(groot::network_handle *handle, int status) noexcept
    {
        if (status != 0) {
            logerror("Failed to accept new connection: %s (%s).", uv_strerror(status), uv_err_name(status));
            return;
        }

        auto server_connection { _connections->get(handle) };
        auto client_connection {
            _connections->acquire(server_connection->version(), connection::side::REMOTE, connection::kind::CLIENT)
        };
        client_connection->init(_loop, this);

        if (server_connection->accept(client_connection)) {
            lognotice("Accepted new connection 0x%" PRIxPTR ".", client_connection);
            client_connection->set_nodelay(true);
            client_connection->set_nonblock(true);
            if (!start_connection(client_connection)) {
                logerror("Failed to start read connection 0x%" PRIxPTR ".", client_connection);
                shutdown_connection(client_connection);
            }
        } else {
            logerror("Failed to accept connection.");
            _connections->release(client_connection);
        }
    }

    void tcp_service::on_connect(uv_connect_t *request, int status) noexcept
    {
        auto handle { reinterpret_cast<groot::network_handle *>(request->handle) };
        auto connection { _connections->get(handle) };
        if (status == 0 && connection != nullptr) {
            lognotice("Successfully connected 0x%" PRIxPTR ".", connection);
            if (!start_connection(connection)) {
                logerror("Cant start read connection 0x%" PRIxPTR ".", connection);
                shutdown_connection(connection);
            }
        } else {
            if (connection != nullptr) {
                logerror("Failed to connect. Shutting down connection 0x%" PRIxPTR ".", connection);
                shutdown_connection(connection);
            }
        }
    }

    void tcp_service::on_alloc(groot::network_handle *handle, size_t suggested_size, uv_buf_t *buffer) noexcept
    {
        auto connection { _connections->get(handle) };
        if (connection == nullptr) {
            logerror("Failed to alloc: connection not found.");
            return;
        }
    }

    void tcp_service::on_read(groot::network_handle *handle, ssize_t nread, const uv_buf_t *buffer) noexcept
    {
        auto connection { _connections->get(handle) };
        if (connection == nullptr) {
            logerror("Failed to read: connection not found.");
            return;
        }
    }

    void tcp_service::on_shutdown(uv_shutdown_t *request, int status) noexcept
    {
        if (status == 0) {
            auto handle = reinterpret_cast<groot::network_handle *>(request->handle);
            auto connection = _connections->get(handle);
            if (connection) {
                lognotice("Shutting down connection 0x%" PRIxPTR ".", connection);
                _connections->release(connection);
            } else {
                logerror("Failed to shutdown connection: not found.");
            }
        } else {
            logerror("Failed to shutdown connection: %s (%s).", uv_strerror(status), uv_err_name(status));
        }
    }

    // static
    void tcp_service::connection_routine(uv_stream_t *stream, int status) noexcept
    {
        if (stream != nullptr && stream->data != nullptr) {
            static_cast<tcp_service *>(stream->data)->
                    on_connection(reinterpret_cast<groot::network_handle *>(stream), status);
        } else {
            logerror("Failed process new connection: %s (%s).", uv_strerror(status), uv_err_name(status));
        }
    }

    // static
    void tcp_service::connect_routine(uv_connect_t *request, int status) noexcept
    {
        if (request != nullptr && request->data != nullptr) {
            static_cast<tcp_service *>(request->data)->on_connect(request, status);
        } else {
            logerror("Failed to process connect: %s (%s).", uv_strerror(status), uv_err_name(status));
        }
    }

    // static
    void tcp_service::alloc_routine(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buffer) noexcept
    {
        if (handle != nullptr && handle->data != nullptr) {
            static_cast<tcp_service *>(handle->data)->
                    on_alloc(reinterpret_cast<groot::network_handle *>(handle), suggested_size, buffer);
        }
    }

    // static
    void tcp_service::read_routine(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buffer) noexcept
    {
        if (stream != nullptr && stream->data != nullptr) {
            static_cast<tcp_service *>(stream->data)->
                    on_read(reinterpret_cast<groot::network_handle *>(stream), nread, buffer);
        }
    }

    // static
    void tcp_service::shutdown_routine(uv_shutdown_t *request, int status) noexcept
    {
        if (request != nullptr && request->data != nullptr) {
            static_cast<tcp_service *>(request->data)->on_shutdown(request, status);
        } else {
            logerror("Failed to shutdown connection: %s (%s).", uv_strerror(status), uv_err_name(status));
        }
    }

}

#undef start_connection
#undef shutdown_connection
