/**
 * @file connection_link.h
 * @author Feo
 * @date 24/09/2018
 * @brief
 */

#ifndef ENGINE_CONNECTION_LINK_H
#define ENGINE_CONNECTION_LINK_H

#include <stl.h>

#include "context/io/net/network.h"

namespace engine {

    class connection;

    /**
     *
     */
    class connection_link final {
    public:
        connection_link() :
                _protocol { transport_protocol::undefined },
                _session_id { 0 },
                _connection_id { 0 },
                _side { connection_side::undefined },
                _kind { connection_kind::undefined }
        {}

        connection_link(const connection_link& other) = default;
        connection_link(connection_link&& other) = default;

        connection_link& operator=(const connection_link&) = default;
        connection_link& operator=(connection_link&&) = default;

        inline transport_protocol protocol() const noexcept { return _protocol; }
        inline size_t session_id() const noexcept { return _session_id; }
        inline u64 connection_id() const noexcept { return _connection_id; }
        inline connection_side side() const noexcept { return _side; }
        inline connection_kind kind() const noexcept { return _kind; }

        size_t hash() const noexcept;

        bool operator==(const connection_link& other) const noexcept {
            return _protocol == other._protocol && _connection_id == other._connection_id;
        }

        bool operator!=(const connection_link& other) const noexcept {
            return !(*this == other);
        }

    private:
        friend class connection;

        transport_protocol          _protocol;
        size_t                      _session_id;
        u64                         _connection_id;
        connection_side             _side;
        connection_kind             _kind;

        explicit connection_link(connection *connection) noexcept;

    };

}

namespace std {

    template<>
    struct hash<engine::connection_link> {
        size_t operator()(const engine::connection_link& link) const noexcept {
            return link.hash();
        }
    };

}

#endif /* ENGINE_CONNECTION_LINK_H */
