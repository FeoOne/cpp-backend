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
        GR_DECLARE_SMARTPOINTERS(connection_manager)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(connection_manager)

        connection_manager();
        ~connection_manager() = default;

        void add(connection *connection) noexcept;
        void remove(connection *connection) noexcept;

        /**
         * @todo: is it method really necessary?
         *  Is connection manager really necessary?
         *  First of all - libuv associate and controlling handles.
         *  Next - high level data structs, like class which represent
         *  logical entity can associate connection too.
         */
        connection *get(groot::network_handle *handle) noexcept;

    private:
        std::unordered_map<groot::network_handle *, connection *>   _connections;

    };

}

#endif /* ROCKET_CONNECTION_MANAGER_H */
