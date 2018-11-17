/**
 * @file connection.h
 * @author Feo
 * @date 28/09/2018
 * @brief
 */

#ifndef ENGINE_CONNECTION_H
#define ENGINE_CONNECTION_H

#include <uv.h>

#include <stl.h>

#include "context/io/connection/connection_link.h"

namespace engine {

    class connection {
    public:
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(connection)

        virtual ~connection() = default;

        void construct(u64 id) noexcept;
        void destruct() noexcept;

        void setup(size_t session_id,
                   const std::string_view& name,
                   const std::string_view& listen,
                   u16 port,
                   u16 backlog,
                   u16 keepalive) noexcept;

        void setup(size_t session_id,
                   const std::string_view& name,
                   const std::string_view& host,
                   u16 port) noexcept;

        void setup(connection *master_connection) noexcept;

        virtual bool open(uv_loop_t *loop, void *data) noexcept = 0;

        void close(uv_close_cb cb) noexcept;

        virtual bool start(uv_alloc_cb alloc_cb, uv_read_cb read_cb) noexcept = 0;
        virtual void stop() noexcept = 0;

        inline size_t id() const noexcept { return _id; }
        inline network_handle *handle() noexcept { return &_handle; }
        inline socket_type protocol() const noexcept { return _protocol; }
        inline connection_side side() const noexcept { return _side; }
        inline connection_kind kind() const noexcept { return _kind; }
        inline protocol_domain version() const noexcept { return _version; }

        inline connection_link link() noexcept { return connection_link { this }; }

        inline connection_status status() const noexcept { return _status; }
        inline void status(connection_status status) noexcept { _status = status; }

        inline size_t session_id() const noexcept { return _session_id; }
        inline const std::string_view& name() const noexcept { return _name; }

    protected:
        explicit connection(socket_type protocol) noexcept;

        inline u16 backlog() const noexcept { return _backlog; }
        inline u16 keepalive() const noexcept { return _keepalive; }
        inline const socket_address *addr() const noexcept { return &_addr; }

    private:
        u64                         _id;

        network_handle              _handle;
        socket_type          _protocol;
        protocol_domain   _version;
        connection_status           _status;
        connection_side             _side;
        connection_kind             _kind;
        socket_address              _addr;
        connection *                _master_connection;

        size_t                      _session_id;
        std::string_view            _name;
        std::string_view            _host;
        u16                         _port;
        u16                         _backlog;
        u16                         _keepalive;

        void setup_sockaddr() noexcept;

    };

}

#endif /* ENGINE_CONNECTION_H */
