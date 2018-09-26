/**
 * @file connection_context.cpp
 * @author Feo
 * @date 24/09/2018
 * @brief
 */

#include "io/connection/tcp_connection.h"
#include "io/connection/udp_connection.h"

#include "io/connection/connection_link.h"

namespace rocket {

    connection_link::connection_link(tcp_connection *connection) noexcept :
            _protocol { groot::network_protocol::TCP },
            _connection_id { connection->id() }
    {
    }

    connection_link::connection_link(udp_connection *connection) noexcept :
            _protocol { groot::network_protocol::UDP },
            _connection_id { 0 }
    {
    }

}
