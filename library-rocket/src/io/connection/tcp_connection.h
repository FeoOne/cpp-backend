/**
 * @file tcp_connection.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ROCKET_TCP_CONNECTION_H
#define ROCKET_TCP_CONNECTION_H

#include <groot.h>

#include "io/connection/io_stream.h"
#include "io/connection/connection_link.h"

namespace rocket {

    class tcp_connection final {
    public:
        GR_DECLARE_SMARTPOINTERS(tcp_connection)
        GR_DELETE_ALL_DEFAULT(tcp_connection)

        ~tcp_connection();

        void init(uv_loop_t *loop, void *data) noexcept;
        bool bind(groot::socket_address *addr) noexcept;
        bool listen(u16 backlog, uv_connection_cb cb) noexcept;
        bool accept(tcp_connection *client_connection) noexcept;
        bool start(uv_alloc_cb alloc_cb, uv_read_cb read_cb) noexcept;
        void stop() noexcept;
        uv_connect_t *connect(groot::socket_address *addr, uv_connect_cb cb) noexcept;
        uv_shutdown_t *shutdown(uv_shutdown_cb cb) noexcept;
        void close(uv_close_cb cb) noexcept;

        void set_nodelay(bool enable) noexcept;
        void set_nonblock(bool enable) noexcept;
        void set_keepalive(bool enable, u32 delay) noexcept;

        size_t id() const noexcept { return _id; }
        groot::network_handle *handle() noexcept { return &_handle; }
        groot::ip_version version() const noexcept { return _version; }
        groot::connection_side side() const noexcept { return _side; }
        groot::connection_kind kind() const noexcept { return _kind; }

        io_stream *read_stream() noexcept { return &_read_stream; }

        inline connection_link link() noexcept { return connection_link { this }; }

    private:
        template<typename>
        friend class connection_manager;

        u64                         _id;
        groot::network_handle       _handle;
        groot::ip_version           _version;
        groot::connection_side      _side;
        groot::connection_kind      _kind;
        io_stream                   _read_stream;
        uv_write_t                  _write_request;
        uv_connect_t                _connect_request;
        uv_shutdown_t               _shutdown_request;

        explicit tcp_connection(u64 id,
                                groot::ip_version version,
                                groot::connection_side side,
                                groot::connection_kind kind) noexcept;

    };

}

#endif /* ROCKET_TCP_CONNECTION_H */
