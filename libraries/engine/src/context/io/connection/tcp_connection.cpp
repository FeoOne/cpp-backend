/**
 * @file tcp_connection.cpp
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#include "main/engine_consts.h"

#include "context/io/connection/tcp_connection.h"

#define check_status(status) \
        logassert(status == 0, "Invalid status: %s (%s).", uv_strerror(status), uv_err_name(status))

namespace engine {

    tcp_connection::tcp_connection() :
            connection(transport_protocol::tcp),
            _read_stream { consts::net::read_stream_size },
            _write_stream { consts::net::write_stream_size },
            _connect_request {},
            _shutdown_request {}
    {
    }

    // virtual
    bool tcp_connection::open(uv_loop_t *loop, void *data) noexcept
    {
        int status { uv_tcp_init(loop, &handle()->tcp) };
        check_status(status);
        uv_handle_set_data(&handle()->handle, data);
    }

    // virtual
    bool tcp_connection::start(uv_alloc_cb alloc_cb, uv_read_cb read_cb) noexcept
    {
        int status { uv_read_start(&handle()->stream, alloc_cb, read_cb) };
        check_status(status);
        return (status == 0);
    }

    // virtual
    void tcp_connection::stop() noexcept
    {
        int status { uv_read_stop(&handle()->stream) };
        check_status(status);
    }

    bool tcp_connection::bind() noexcept
    {
        int status { uv_tcp_bind(&handle()->tcp, &addr()->sa, 0) };
        check_status(status);
        return (status == 0);
    }

    bool tcp_connection::listen(uv_connection_cb cb) noexcept
    {
        int status { uv_listen(&handle()->stream, backlog(), cb) };
        check_status(status);
        return (status == 0);
    }

    bool tcp_connection::accept(tcp_connection *client_connection) noexcept
    {
        int status { uv_accept(&handle()->stream, &client_connection->handle()->stream) };
        check_status(status);
        return (status == 0);
    }

    uv_connect_t *tcp_connection::connect(uv_connect_cb cb) noexcept
    {
        int status { uv_tcp_connect(&_connect_request, &handle()->tcp, &addr()->sa, cb) };
        if (status != 0) {
            logerror("Failed to connect: %s (%s).", uv_strerror(status), uv_err_name(status));
        } else {
            _connect_request.data = handle()->handle.data;
        }
        return &_connect_request;
    }

    void tcp_connection::write() noexcept
    {
        uv_buf_t buf { reinterpret_cast<char *>(_write_stream.head()), _write_stream.useful_size() };
        auto status { uv_try_write(&handle()->stream, &buf, 1) };
        if (status > 0) {
            _write_stream.increase_head(static_cast<size_t>(status));
            _write_stream.flush_if_needed();
        }

        logdebug("Writing for cid: %llu, length: %d, buffer size: %lu.", id(), status, buf.len);
    }

    uv_shutdown_t *tcp_connection::shutdown(uv_shutdown_cb cb) noexcept
    {
        int status { uv_shutdown(&_shutdown_request, &handle()->stream, cb) };
        if (status != 0) {
            logerror("Failed to shutdown: %s (%s).", uv_strerror(status), uv_err_name(status));
        } else {
            _shutdown_request.data = handle()->handle.data;
        }
        return &_shutdown_request;
    }

    void tcp_connection::set_nodelay(bool enable) noexcept
    {
        int status { uv_tcp_nodelay(&handle()->tcp, enable ? 1 : 0) };
        check_status(status);
    }

    void tcp_connection::set_nonblock(bool enable) noexcept
    {
        int status { uv_stream_set_blocking(&handle()->stream, enable ? 0 : 1) };
        check_status(status);
    }

    void tcp_connection::set_keepalive(bool enable) noexcept
    {
        int status { uv_tcp_keepalive(&handle()->tcp, enable ? 1 : 0, keepalive()) };
        check_status(status);
    }

}

#undef check_status
