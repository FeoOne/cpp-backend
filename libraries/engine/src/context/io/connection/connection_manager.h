/**
 * @file connection_manager.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ENGINE_CONNECTION_MANAGER_H
#define ENGINE_CONNECTION_MANAGER_H

#include "main/engine_consts.h"
#include "context/io/connection/tcp_connection.h"
#include "context/io/connection/udp_connection.h"

namespace engine {

    template<typename T>
    class connection_manager final {
    public:
        STL_DECLARE_SMARTPOINTERS(connection_manager)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(connection_manager)

        using connection_type = T;
        using connection_pointer = T *;

        /**
         * Ctor.
         * @param input_buffer_size
         * @param output_buffer_size
         */
        connection_manager() :
                _id_counter { 0 },
                _connections_by_id {},
                _connection_pool { connection_pool::make_unique() }
        {
            _connections_by_id.reserve(consts::IO_CONNECTION_RESERVE_COUNT);
            _connections_by_handle.reserve(consts::IO_CONNECTION_RESERVE_COUNT);
        }

        ~connection_manager() = default;

        /**
         * Acquire new connection.
         * @param version
         * @param side
         * @param kind
         * @return
         */
        inline connection_pointer produce() noexcept {
            // increment connection id counter
            do {
                ++_id_counter;
            } while (_id_counter == 0); // 0 id = invalid connection

            // create connection
            auto connection { _connection_pool->acquire() };
            connection->construct(_id_counter);

            logdebug("Acquired connection with id: %lu.", connection->id());

            _connections_by_id.insert({ connection->id(), connection });
            _connections_by_handle.insert({ connection->handle(), connection });

            return connection;
        }

        /**
         * Return unnecessary connection.
         * @param connection Connection to release.
         */
        inline void consume(connection_pointer connection) noexcept {
            if (connection == nullptr) {
                logerror("Can't release null pointer.");
                return;
            }

            // by id
            auto it_by_id = _connections_by_id.find(connection->id());
            if (it_by_id == _connections_by_id.end()) {
                logerror("Connection with id %lu not presented.", connection->id());
                return;
            }

            // by handle
            auto it_by_handle = _connections_by_handle.find(connection->handle());
            if (it_by_handle == _connections_by_handle.end()) {
                logerror("Connection handle with id %lu not presented.", connection->id());
                return;
            }

            _connections_by_id.erase(it_by_id);
            _connections_by_handle.erase(it_by_handle);

            logdebug("Released connection with id %lu.", connection->id());

            connection->destruct();
            _connection_pool->release(connection);
        }

        /**
         * Get connection by handle.
         * @param handle Connection's handle.
         * @return Connection pointer if `handle` presented, `nullptr` otherwise.
         */
        inline connection_pointer get(network_handle *handle) noexcept {
            if (handle == nullptr) {
                return nullptr;
            }

            connection_pointer connection { nullptr };

            auto it = _connections_by_handle.find(handle);
            if (it != _connections_by_handle.end()) {
                connection = it->second;
            }

            return connection;
        }

        /**
         * Get connection by id.
         * @param id Connection's id.
         * @return Connection pointer if `id` presented, `nullptr` otherwise.
         */
        inline connection_pointer get(u64 id) noexcept {
            if (id == 0) {
                return nullptr;
            }

            connection_pointer connection { nullptr };

            auto it = _connections_by_id.find(id);
            if (it != _connections_by_id.end()) {
                connection = it->second;
            }

            return connection;
        }

        /**
         * Get connection by link.
         * @param link Connection's link.
         * @return Connection pointer if `link.id()` presented, `nullptr` otherwise.
         */
        inline connection_pointer get(const connection_link& link) noexcept {
            return get(link.connection_id());
        }

    private:
        using connection_pool = stl::object_pool<connection_type>;

        u64                                                         _id_counter;
        std::unordered_map<u64, connection_pointer>                 _connections_by_id;
        std::unordered_map<network_handle *, connection_pointer>    _connections_by_handle;
        typename connection_pool::uptr                              _connection_pool;

    };

    using tcp_connection_manager = connection_manager<tcp_connection>;
    using udp_connection_manager = connection_manager<udp_connection>;

}

#endif /* ENGINE_CONNECTION_MANAGER_H */
