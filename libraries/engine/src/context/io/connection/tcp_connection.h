/**
 * @file tcp_connection.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ENGINE_TCP_CONNECTION_H
#define ENGINE_TCP_CONNECTION_H

#include "context/io/stream/tcp_stream.h"
#include "context/io/stream/tcp_stream.h"
#include "context/io/connection/connection.h"

namespace engine {

    class tcp_connection final : public connection {
    public:
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(tcp_connection)

        tcp_connection();
        virtual ~tcp_connection() = default;

        bool open(uv_loop_t *loop, void *data) noexcept final;

        bool start(uv_alloc_cb alloc_cb, uv_read_cb read_cb) noexcept final;
        void stop() noexcept final;

        // master
        bool bind() noexcept;
        bool listen(uv_connection_cb cb) noexcept;
        bool accept(tcp_connection *client_connection) noexcept;

        // slave
        uv_connect_t *connect(uv_connect_cb cb) noexcept;

        void write() noexcept;
        uv_shutdown_t *shutdown(uv_shutdown_cb cb) noexcept;

        void set_nodelay(bool enable) noexcept;
        void set_nonblock(bool enable) noexcept;
        void set_keepalive(bool enable) noexcept;

        inline tcp_stream *read_stream() noexcept { return &_read_stream; }
        inline tcp_stream *write_stream() noexcept { return &_write_stream; }

    private:
        tcp_stream             _read_stream;
        tcp_stream            _write_stream;

        uv_connect_t                _connect_request;
        uv_shutdown_t               _shutdown_request;

    };

}

#endif /* ENGINE_TCP_CONNECTION_H */
