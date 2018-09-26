/**
 * @file connection_link.h
 * @author Feo
 * @date 24/09/2018
 * @brief
 */

#ifndef ROCKET_CONNECTION_LINK_H
#define ROCKET_CONNECTION_LINK_H

#include <groot.h>

namespace rocket {

    class tcp_connection;
    class udp_connection;

    /**
     *
     */
    class connection_link final {
    public:
        GR_DELETE_DEFAULT_CTOR(connection_link)
        GR_DELETE_DEFAULT_COPY_ASSIGN(connection_link)
        GR_DELETE_DEFAULT_MOVE_CTOR(connection_link)
        GR_DELETE_DEFAULT_MOVE_ASSIGN(connection_link)

        connection_link(const connection_link& other) = default;

        groot::network_protocol protocol() const noexcept { return _protocol; }
        u64 connection_id() const noexcept { return _connection_id; }

    private:
        friend class tcp_connection;
        friend class udp_connection;

        groot::network_protocol     _protocol;
        u64                         _connection_id;

        explicit connection_link(tcp_connection *connection) noexcept;
        explicit connection_link(udp_connection *connection) noexcept;

    };

}

#endif /* ROCKET_CONNECTION_LINK_H */
