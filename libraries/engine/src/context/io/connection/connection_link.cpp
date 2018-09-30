/**
 * @file connection_context.cpp
 * @author Feo
 * @date 24/09/2018
 * @brief
 */

#include "context/io/connection/connection.h"

#include "context/io/connection/connection_link.h"

namespace engine {

    connection_link::connection_link(connection *connection) noexcept :
            _protocol { connection->protocol() },
            _connection_id { connection->id() }
    {
    }

}
