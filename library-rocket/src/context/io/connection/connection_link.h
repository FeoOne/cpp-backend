/**
 * @file connection_link.h
 * @author Feo
 * @date 24/09/2018
 * @brief
 */

#ifndef ROCKET_CONNECTION_LINK_H
#define ROCKET_CONNECTION_LINK_H

#include <groot.h>

#include "context/io/net/network.h"

namespace rocket {

    class connection;

    /**
     *
     */
    class connection_link final {
    public:
        GR_DELETE_DEFAULT_CTOR(connection_link)

        connection_link(const connection_link& other) = default;
        connection_link(connection_link&& other) = default;

        connection_link& operator=(const connection_link&) = default;
        connection_link& operator=(connection_link&&) = default;

        transport_protocol protocol() const noexcept { return _protocol; }
        u64 connection_id() const noexcept { return _connection_id; }

    private:
        friend class connection;

        transport_protocol          _protocol;
        u64                         _connection_id;

        explicit connection_link(connection *connection) noexcept;

    };

}

#endif /* ROCKET_CONNECTION_LINK_H */
