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

        virtual ~connection() = default;

        virtual void init(uv_loop_t *loop, void *data) noexcept = 0;
        virtual bool bind(framework::socket_address *addr) noexcept = 0;
        virtual bool listen(u16 backlog, uv_connection_cb cb) noexcept = 0;
        virtual bool accept(const connection::sptr& connection) noexcept = 0;
        virtual uv_connect_t *connect(framework::socket_address *addr, uv_connect_cb cb) noexcept = 0;
        virtual uv_shutdown_t *shutdown(uv_shutdown_cb cb) noexcept = 0;

        virtual void set_nodelay(bool enable) noexcept = 0;
        virtual void set_nonblock(bool enable) noexcept = 0;
        virtual void set_keepalive(bool enable, u32 delay) noexcept = 0;

        framework::network_handle *get_handle() noexcept { return &_handle; }
        framework::network_protocol get_protocol() const noexcept { return _proto; }
        framework::ip_version get_version() const noexcept { return _version; }
        side_t get_side() const noexcept { return _side; }
        kind_t get_kind() const noexcept { return _kind; }

    protected:
        explicit connection(framework::network_protocol proto,
                            framework::ip_version version,
                            side_t side,
                            kind_t kind) noexcept;

    private:
        framework::network_handle                       _handle;
        framework::network_protocol                     _proto;
        framework::ip_version                           _version;
        side_t                                          _side;
        kind_t                                          _kind;

    };

}

#endif /* ENGINE_CONNECTION_H */
