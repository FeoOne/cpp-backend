/**
 * @file tcp_connection.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ROCKET_TCP_CONNECTION_H
#define ROCKET_TCP_CONNECTION_H

#include "io/connection/connection.h"

namespace rocket {

    class tcp_connection final : public connection {
    public:
        GR_DECLARE_SMARTPOINTERS(tcp_connection)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(tcp_connection)

        explicit tcp_connection(groot::ip_version version,
                                side side,
                                kind kind) noexcept;

        virtual ~tcp_connection() = default;

        void init(uv_loop_t *loop, void *data) noexcept final;
        bool bind(groot::socket_address *addr) noexcept final;
        bool listen(u16 backlog, uv_connection_cb cb) noexcept final;
        bool accept(connection *connection) noexcept final;
        bool start(uv_alloc_cb alloc_cb, uv_read_cb read_cb) noexcept final;
        uv_connect_t *connect(groot::socket_address *addr, uv_connect_cb cb) noexcept final;
        uv_shutdown_t *shutdown(uv_shutdown_cb cb) noexcept final;

        void set_nodelay(bool enable) noexcept final;
        void set_nonblock(bool enable) noexcept final;
        void set_keepalive(bool enable, u32 delay) noexcept final;

    };

}

#endif /* ROCKET_TCP_CONNECTION_H */
