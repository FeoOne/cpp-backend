/**
 * @file tcp_connection.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ENGINE_TCP_CONNECTION_H
#define ENGINE_TCP_CONNECTION_H

#include "io/connection/connection.h"

namespace engine {

    class tcp_connection final : public connection {
    public:
        FW_DECLARE_SMARTPOINTERS(tcp_connection)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(tcp_connection)

        explicit tcp_connection(framework::ip_version version,
                                side_t side,
                                kind_t kind) noexcept;

        virtual ~tcp_connection() = default;

        void init(uv_loop_t *loop, void *data) noexcept final;
        bool bind(framework::socket_address *addr) noexcept final;
        bool listen(u16 backlog, uv_connection_cb cb) noexcept final;
        bool accept(const connection::sptr& connection) noexcept;
        uv_connect_t *connect(framework::socket_address *addr, uv_connect_cb cb) noexcept final;
        uv_shutdown_t *shutdown(uv_shutdown_cb cb) noexcept final;

        void set_nodelay(bool enable) noexcept final;
        void set_nonblock(bool enable) noexcept final;
        void set_keepalive(bool enable, u32 delay) noexcept final;

    private:

    };

}

#endif /* ENGINE_TCP_CONNECTION_H */
