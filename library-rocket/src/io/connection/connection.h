/**
 * @file connection.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ROCKET_CONNECTION_H
#define ROCKET_CONNECTION_H

#include <groot.h>

namespace rocket {

    class connection {
    public:
        GR_DECLARE_SMARTPOINTERS(connection)

        enum class side {
            LOCAL,
            REMOTE,
        };

        enum class kind {
            CLIENT,
            SERVER,
        };

        virtual ~connection() = default;

        virtual void init(uv_loop_t *loop, void *data) noexcept = 0;
        virtual bool bind(groot::socket_address *addr) noexcept = 0;
        virtual bool listen(u16 backlog, uv_connection_cb cb) noexcept = 0;
        virtual bool accept(connection *connection) noexcept = 0;
        virtual uv_connect_t *connect(groot::socket_address *addr, uv_connect_cb cb) noexcept = 0;
        virtual uv_shutdown_t *shutdown(uv_shutdown_cb cb) noexcept = 0;

        virtual void set_nodelay(bool enable) noexcept = 0;
        virtual void set_nonblock(bool enable) noexcept = 0;
        virtual void set_keepalive(bool enable, u32 delay) noexcept = 0;

        groot::network_handle *get_handle() noexcept { return &_handle; }
        groot::network_protocol get_protocol() const noexcept { return _proto; }
        groot::ip_version get_version() const noexcept { return _version; }
        side get_side() const noexcept { return _side; }
        kind get_kind() const noexcept { return _kind; }

    protected:
        explicit connection(groot::network_protocol proto,
                            groot::ip_version version,
                            side side,
                            kind kind) noexcept;

    private:
        groot::network_handle       _handle;
        groot::network_protocol     _proto;
        groot::ip_version           _version;
        side                      _side;
        kind                      _kind;

    };

}

#endif /* ROCKET_CONNECTION_H */
