/**
 * @file connection.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "io/connection/connection.h"

using namespace framework;

namespace engine {

    connection::connection(network_protocol proto,
                           ip_version version,
                           side_t side,
                           kind_t kind) noexcept :
            _handle {},
            _proto { proto },
            _version { version },
            _side { side },
            _kind { kind }
    {
    }

    void connection::init(uv_loop_t *loop, void *data) noexcept
    {
        int status;
        switch (_proto) {
            case network_protocol::TCP: {
                status = uv_tcp_init(loop, &_handle.tcp);
                break;
            }
            case network_protocol::UDP: {
                status = uv_udp_init(loop, &_handle.udp);
                break;
            }
        }
        logassert(status == 0);
        _handle.handle.data = data;
    }

    bool connection::bind(socket_address *addr) noexcept
    {
        int status = uv_tcp_bind(&_handle.tcp, &addr->sa, 0);
        logassert(status == 0);
        return (status == 0);
    }

    bool connection::listen(u16 backlog, uv_connection_cb cb) noexcept
    {
        int status = uv_listen(&_handle.stream, backlog, cb);
        logassert(status == 0);
        return (status == 0);
    }

    uv_connect_t *connection::connect(framework::socket_address *addr, uv_connect_cb cb) noexcept
    {
        uv_connect_t *request { new (std::nothrow) uv_connect_t };

        int status = uv_tcp_connect(request, &_handle.tcp, &addr->sa, cb);
    }

    void connection::set_nodelay(bool enable) noexcept
    {
        int status = uv_tcp_nodelay(&_handle.tcp, enable ? 1 : 0);
        logassert(status == 0);
    }

    void connection::set_nonblock(bool enable) noexcept
    {
        int status = uv_stream_set_blocking(&_handle.stream, enable ? 0 : 1);
        logassert(status == 0);
    }

    void connection::set_keepalive(bool enable, u32 delay) noexcept
    {
        int status = uv_tcp_keepalive(&_handle.tcp, enable ? 1 : 0, delay);
        logassert(status == 0);
    }

}
