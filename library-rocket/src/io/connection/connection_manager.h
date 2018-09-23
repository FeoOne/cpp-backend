/**
 * @file connection_manager.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ROCKET_CONNECTION_MANAGER_H
#define ROCKET_CONNECTION_MANAGER_H

#include "main/rocket_consts.h"
#include "io/connection/tcp_connection.h"
#include "io/connection/udp_connection.h"

#define RC_CONNECTION_POOL_PAGE_SIZE    groot::memory::page_size() * 16

namespace rocket {

    template<typename T>
    class connection_manager final {
    public:
        GR_DECLARE_SMARTPOINTERS(connection_manager)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(connection_manager)

        using connection_type = T;
        using connection_pointer = T *;

        /**
         * Ctor.
         * @param input_buffer_size
         * @param output_buffer_size
         */
        connection_manager() :
                _connections {},
                _connection_pool {
                    groot::fixed_memory_pool::make_unique(sizeof(connection_type), RC_CONNECTION_POOL_PAGE_SIZE)
                }
        {
            _connections.reserve(consts::IO_CONNECTION_RESERVE_COUNT);
        }

        ~connection_manager() = default;

        /**
         * Acquire new connection.
         * @param handle
         * @param version
         * @param side
         * @param kind
         * @return
         */
        connection_pointer acquire(groot::ip_version version,
                                   connection::side side,
                                   connection::kind kind) noexcept {
            auto connection {
                new (_connection_pool->alloc()) connection_type(version, side, kind)
            };

            if (connection != nullptr) {
                _connections.insert({ connection->handle(), connection });
                logdebug("Acquired connection 0x%" PRIxPTR ".", connection);
            } else {
                logerror("Failed to acquire connection.");
            }

            return connection;
        }

        /**
         * Return unnecessary connection.
         * @param connection Connection to release.
         */
        void release(connection_pointer connection) noexcept {
            if (connection == nullptr) {
                logerror("Can't release null pointer.");
                return;
            }

            auto it = _connections.find(connection->handle());
            if (it == _connections.end()) {
                logerror("Can't find connection to release.");
                return;
            }

            _connections.erase(it);

            logdebug("Released connection 0x%" PRIxPTR ".", connection);

            _connection_pool->free(connection);
        }

        /**
         *
         * @param handle
         * @return
         */
        connection_pointer get(groot::network_handle *handle) noexcept {
            connection_pointer connection { nullptr };
            auto it = _connections.find(connection->handle());
            if (it != _connections.end()) {
                connection = it->second;
            }
            return connection;
        }

    private:
        std::unordered_map<groot::network_handle *, connection_pointer> _connections;
        groot::fixed_memory_pool::uptr                                  _connection_pool;

    };

    using tcp_connection_manager = connection_manager<tcp_connection>;
    using udp_connection_manager = connection_manager<udp_connection>;

}

#endif /* ROCKET_CONNECTION_MANAGER_H */
