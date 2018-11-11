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
            _session_id { connection->session_id() },
            _connection_id { connection->id() },
            _side { connection->side() },
            _kind { connection->kind() }
    {
    }

    size_t connection_link::hash() const noexcept
    {
        return static_cast<size_t>(_connection_id);
    }

}
