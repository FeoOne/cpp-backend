/**
 * @file tcp_service.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "io/io_loop.h"
#include "io/connection/connection.h"

#include "io/service/tcp_service.h"

using namespace framework;

namespace engine {

    tcp_service::tcp_service(const config_setting::sptr& config,
                             const task_router::sptr& router,
                             const work_context_delegate *service_provider) noexcept :
            crucial(config, router, service_provider),
            _loop { nullptr }
    {
    }

    // virtual
    tcp_service::~tcp_service()
    {
    }

    void tcp_service::setup() noexcept
    {
        _loop = get_context_delegate()->get_own_loop<io_loop>()->get_loop();
    }

    void tcp_service::reset() noexcept
    {
        _loop = nullptr;
    }

    void tcp_service::listen(const framework::endpoint::sptr& endpoint,
                             u16 backlog,
                             u32 keepalive) noexcept
    {
        auto connection = connection::make_shared(network_protocol::TCP,
                endpoint->get_version(),
                connection::side_t::LOCAL,
                connection::kind_t::SERVER);
        connection->init(_loop, this);
        connection->set_nodelay(true);
        connection->set_nonblock(true);
        connection->set_keepalive(true, keepalive);

        socket_address addr {};
        setup_sockaddr(endpoint, &addr);

        if (connection->bind(&addr) && connection->listen(backlog, &tcp_service::connection_routine)) {
            lognotice("Successfully started server socket %s:%u.", endpoint->get_port(), endpoint->get_port());

            // @todo Add connection.
        } else {
            logerror("Failed to start server socket %s:%u.", endpoint->get_port(), endpoint->get_port());
        }
    }

    void tcp_service::connect(const framework::endpoint::sptr& endpoint) noexcept
    {
        auto connection = connection::make_shared(network_protocol::TCP,
                endpoint->get_version(),
                connection::side_t::LOCAL,
                connection::kind_t::CLIENT);
        connection->init(_loop, this);
        connection->set_nonblock(true);

        socket_address addr {};
        setup_sockaddr(endpoint, &addr);


    }

    void tcp_service::setup_sockaddr(const endpoint::sptr& endpoint, socket_address *addr) noexcept
    {
        switch (endpoint->get_version()) {
            case ip_version::IPV4: {
                uv_ip4_addr(endpoint->get_host().data(), endpoint->get_port(), &addr->sin);
                break;
            }
            case ip_version::IPV6: {
                uv_ip6_addr(endpoint->get_host().data(), endpoint->get_port(), &addr->sin6);
                break;
            }
        }
    }

    void tcp_service::on_connection(framework::network_handle *handle, int status) noexcept
    {

    }

    // static
    void tcp_service::connection_routine(uv_stream_t *stream, int status) noexcept
    {
        if (stream != nullptr && stream->data != nullptr) {
            static_cast<tcp_service *>(stream->data)->
                    on_connection(reinterpret_cast<network_handle *>(stream), status);
        } else {
            logerror("Failed process new connection (%d).", status);
        }
    }

}
