/**
 * @file tcp_connection.cpp
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#include "io/connection/tcp_connection.h"

namespace rocket {

    tcp_connection::tcp_connection(groot::ip_version version,
                                   side_t side,
                                   kind_t kind) noexcept :
            connection(groot::network_protocol::TCP, version, side, kind)
    {
    }

    void tcp_connection::init(uv_loop_t *loop, void *data) noexcept
    {
        int status = uv_tcp_init(loop, &get_handle()->tcp);
        logassert(status == 0, "Invalid status.");
        get_handle()->handle.data = data;
    }

    bool tcp_connection::bind(groot::socket_address *addr) noexcept
    {
        int status = uv_tcp_bind(&get_handle()->tcp, &addr->sa, 0);
        logassert(status == 0, "Invalid status.");
        return (status == 0);
    }

    bool tcp_connection::listen(u16 backlog, uv_connection_cb cb) noexcept
    {
        int status = uv_listen(&get_handle()->stream, backlog, cb);
        logassert(status == 0, "Invalid status.");
        return (status == 0);
    }

    bool tcp_connection::accept(connection *connection) noexcept
    {
       int status = uv_accept(&get_handle()->stream, &connection->get_handle()->stream);
       logassert(status == 0, "Invalid status.");
        return (status == 0);
    }

    uv_connect_t *tcp_connection::connect(groot::socket_address *addr, uv_connect_cb cb) noexcept
    {
        uv_connect_t *request { new (std::nothrow) uv_connect_t };

        int status = uv_tcp_connect(request, &get_handle()->tcp, &addr->sa, cb);
        if (status != 0) {
            logerror("Failed to connect: %s (%s).", uv_strerror(status), uv_err_name(status));

            delete request;
            request = nullptr;
        } else {
            request->data = get_handle()->handle.data;
        }
        return request;
    }

    uv_shutdown_t *tcp_connection::shutdown(uv_shutdown_cb cb) noexcept
    {
        uv_shutdown_t *request { new (std::nothrow) uv_shutdown_t };
        request->data = get_handle()->handle.data;
        uv_shutdown(request, &get_handle()->stream, cb);
    }

    void tcp_connection::set_nodelay(bool enable) noexcept
    {
        int status = uv_tcp_nodelay(&get_handle()->tcp, enable ? 1 : 0);
        logassert(status == 0, "Invalid status.");
    }

    void tcp_connection::set_nonblock(bool enable) noexcept
    {
        int status = uv_stream_set_blocking(&get_handle()->stream, enable ? 0 : 1);
        logassert(status == 0, "Invalid status.");
    }

    void tcp_connection::set_keepalive(bool enable, u32 delay) noexcept
    {
        int status = uv_tcp_keepalive(&get_handle()->tcp, enable ? 1 : 0, delay);
        logassert(status == 0, "Invalid status.");
    }

}
