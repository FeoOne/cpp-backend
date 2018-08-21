/**
 * @file connection_manager.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ROCKET_CONNECTION_MANAGER_H
#define ROCKET_CONNECTION_MANAGER_H

#include "io/connection/connection.h"

namespace rocket {

    class connection_manager final {
    public:
        FW_DECLARE_SMARTPOINTERS(connection_manager)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(connection_manager)

        connection_manager();
        ~connection_manager() = default;

        void add(const connection::sptr& connection) noexcept;
        void remove(const connection::sptr& connection) noexcept;
        connection::sptr get(groot::network_handle *handle) noexcept;

    private:
        std::unordered_map<groot::network_handle *, connection::sptr>       _connections;

    };

}

#endif /* ROCKET_CONNECTION_MANAGER_H */
