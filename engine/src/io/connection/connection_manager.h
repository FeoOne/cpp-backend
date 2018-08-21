/**
 * @file connection_manager.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ENGINE_CONNECTION_MANAGER_H
#define ENGINE_CONNECTION_MANAGER_H

#include "io/connection/connection.h"

namespace engine {

    class connection_manager final {
    public:
        FW_DECLARE_SMARTPOINTERS(connection_manager)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(connection_manager)

        connection_manager();
        ~connection_manager() = default;

        void add(const connection::sptr& connection) noexcept;
        void remove(const connection::sptr& connection) noexcept;
        connection::sptr get(framework::network_handle *handle) noexcept;

    private:
        std::unordered_map<framework::network_handle *, connection::sptr>       _connections;

    };

}

#endif /* ENGINE_CONNECTION_MANAGER_H */
