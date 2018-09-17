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

namespace rocket {

    tcp_service::tcp_service(const groot::setting& config,
                             task_router *router,
                             const work_service_delegate *service_delegate) noexcept :
            crucial(config, router, service_delegate),
            _loop { nullptr },
            _connections {},
            _connection_pool {
                groot::fixed_memory_pool::make_unique(sizeof(tcp_connection), groot::memory::page_size())
            }
    {
    }

    // virtual
    tcp_service::~tcp_service()
    {
    }

    void tcp_service::setup() noexcept
    {
        _loop = delegate()->get_loop<io_loop>()->get_loop();
    }

    void tcp_service::reset() noexcept
    {
        _loop = nullptr;
    }

    void tcp_service::listen(const groot::endpoint::sptr& endpoint,
                             u16 backlog,
                             u32 keepalive) noexcept
    {
        auto connection = new (_connection_pool->alloc()) tcp_connection(endpoint->get_version(),
                                                                         connection::side_t::LOCAL,
                                                                         connection::kind_t::SERVER);
        connection->init(_loop, this);
        connection->set_nodelay(true);
        connection->set_nonblock(true);
        connection->set_keepalive(true, keepalive);

        groot::socket_address addr {};
        setup_sockaddr(endpoint, &addr);

        if (connection->bind(&addr) && connection->listen(backlog, &tcp_service::connection_routine)) {
            lognotice("Successfully started server socket %s:%u.", endpoint->get_port(), endpoint->get_port());
            _connections->add(connection);
        } else {
            logerror("Failed to start server socket %s:%u.", endpoint->get_port(), endpoint->get_port());
        }
    }

    void tcp_service::connect(const groot::endpoint::sptr& endpoint) noexcept
    {
        auto connection { new (_connection_pool->alloc()) tcp_connection(endpoint->get_version(),
                                                                         connection::side_t::LOCAL,
                                                                         connection::kind_t::CLIENT) };
        connection->init(_loop, this);
        connection->set_nodelay(true);
        connection->set_nonblock(true);

        groot::socket_address addr {};
        setup_sockaddr(endpoint, &addr);

        auto request = connection->connect(&addr, &tcp_service::connect_routine);
        if (request != nullptr) {
            _connections->add(connection);
        }
    }

    void tcp_service::setup_sockaddr(const groot::endpoint::sptr& endpoint,
                                     groot::socket_address *addr) noexcept
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

    void tcp_service::on_connection(groot::network_handle *handle, int status) noexcept
    {
        if (status != 0) {
            logerror("Failed to accept new connection: %s (%s).", uv_strerror(status), uv_err_name(status));
            return;
        }

        auto server_connection { _connections->get(handle) };
        auto client_connection { new (_connection_pool->alloc()) tcp_connection(server_connection->get_version(),
                                                                                connection::side_t::REMOTE,
                                                                                connection::kind_t::CLIENT) };
        client_connection->init(_loop, this);
        client_connection->set_nodelay(true);
        client_connection->set_nonblock(true);

        if (server_connection->accept(client_connection)) {
            _connections->add(client_connection);
            // todo@ Start read.
        } else {
            logerror("Failed to accept connection.");
        }
    }

    void tcp_service::on_connect(uv_connect_t *request, int status) noexcept
    {
        auto handle { reinterpret_cast<groot::network_handle *>(request->handle) };
        auto connection = _connections->get(handle);
        if (status == 0 && connection != nullptr) {
            // @todo Start read.
        } else {
            logerror("Failed to connect. Shutting down connection.");
            if (connection != nullptr) {
                connection->shutdown(&tcp_service::shutdown_routine);
            }
        }
    }

    void tcp_service::on_shutdown(uv_shutdown_t *request, int status) noexcept
    {
        auto handle = reinterpret_cast<groot::network_handle *>(request->handle);
        auto connection = _connections->get(handle);
        if (status == 0 && connection) {
            _connections->remove(connection);
            _connection_pool->free(connection);
        } else {
            logerror("Failed to shutdown connection.");
        }
    }

    // static
    void tcp_service::connection_routine(uv_stream_t *stream, int status) noexcept
    {
        if (stream != nullptr && stream->data != nullptr) {
            static_cast<tcp_service *>(stream->data)->
                    on_connection(reinterpret_cast<groot::network_handle *>(stream), status);
        } else {
            logerror("Failed process new connection (%d).", status);
        }
    }

    // static
    void tcp_service::connect_routine(uv_connect_t *request, int status) noexcept
    {
        if (request != nullptr && request->data != nullptr) {
            static_cast<tcp_service *>(request->data)->on_connect(request, status);
        }
    }

    // static
    void tcp_service::shutdown_routine(uv_shutdown_t *request, int status) noexcept
    {
        if (request != nullptr && request->data != nullptr) {
            static_cast<tcp_service *>(request->data)->on_shutdown(request, status);
        }
    }

}
