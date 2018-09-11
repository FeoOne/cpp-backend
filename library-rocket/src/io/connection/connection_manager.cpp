/**
 * @file connection_manager.cpp
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#include "main/rocket_consts.h"
#include "io/connection/connection_manager.h"

namespace rocket {

    connection_manager::connection_manager() :
            _connections {}
    {
        _connections.reserve(consts::CONNECTION_RESERVE_COUNT);
    }

    void connection_manager::add(connection *connection) noexcept
    {
        auto it = _connections.find(connection->get_handle());
        if (it == _connections.end()) {
            _connections.insert({ connection->get_handle(), connection });
        }
        // @todo Log error.
    }

    void connection_manager::remove(connection *connection) noexcept
    {
        auto it = _connections.find(connection->get_handle());
        if (it != _connections.end()) {
            _connections.erase(it);
        }
        // @todo Log error.
    }

    connection *connection_manager::get(groot::network_handle *handle) noexcept
    {
        connection *c { nullptr };

        auto it = _connections.find(c->get_handle());
        if (it != _connections.end()) {
            c = it->second;
        }

        return c;
    }

}
