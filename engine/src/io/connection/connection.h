/**
 * @file connection.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ENGINE_CONNECTION_H
#define ENGINE_CONNECTION_H

#include <framework.h>

namespace engine {

    class connection {
    public:
        FW_DECLARE_SMARTPOINTERS(connection)

        enum class side_t {
            LOCAL,
            REMOTE,
        };

        enum class kind_t {
            CLIENT,
            SERVER,
        };

        explicit connection(framework::network_protocol proto,
                            framework::ip_version version,
                            side_t side,
                            kind_t kind) noexcept;
        ~connection() = default;

        void init(uv_loop_t *loop, void *data) noexcept;
        bool bind(framework::socket_address *addr) noexcept;
        bool listen(u16 backlog, uv_connection_cb cb) noexcept;
        uv_connect_t *connect(framework::socket_address *addr, uv_connect_cb cb) noexcept;

        void set_nodelay(bool enable) noexcept;
        void set_nonblock(bool enable) noexcept;
        void set_keepalive(bool enable, u32 delay) noexcept;

        framework::network_handle *get_handle() noexcept { return &_handle; }

    private:
        framework::network_handle                       _handle;
        framework::network_protocol                     _proto;
        framework::ip_version                           _version;
        side_t                                          _side;
        kind_t                                          _kind;

    };

}

#endif /* ENGINE_CONNECTION_H */
