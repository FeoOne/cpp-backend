/**
 * @file connection.cpp
 * @author Feo
 * @date 28/09/2018
 * @brief
 */

#include "context/io/connection/connection.h"

namespace engine {

    connection::connection(socket_type protocol) noexcept :
            _id { 0 },
            _handle {},
            _protocol { protocol },
            _version { protocol_domain::undefined },
            _status { connection_status::disconnected },
            _side { connection_side::undefined },
            _kind { connection_kind::undefined },
            _addr {},
            _master_connection { nullptr },
            _name { "" },
            _host { "" },
            _port { 0 },
            _backlog { 0 },
            _keepalive { 0 }
    {
        std::memset(&_addr, 0, sizeof(socket_address));
    }

    void connection::construct(u64 id) noexcept
    {
        _id = id;
    }

    void connection::destruct() noexcept
    {
        _id = 0;
    }

    void connection::close(uv_close_cb cb) noexcept
    {
        if (uv_is_closing(&_handle.handle) == 0) {
            uv_close(&_handle.handle, cb);
        }
    }

    void connection::setup(size_t session_id,
                           const std::string_view& name,
                           const std::string_view& listen,
                           u16 port,
                           u16 backlog,
                           u16 keepalive) noexcept
    {
        _side = connection_side::local;
        _kind = connection_kind::master;

        _session_id = session_id;
        _name = name;
        _host = listen;
        _port = port;
        _backlog = backlog;
        _keepalive = keepalive;

        setup_sockaddr();
    }

    void connection::setup(size_t session_id,
                           const std::string_view& name,
                           const std::string_view& host,
                           u16 port) noexcept
    {
        _side = connection_side::local;
        _kind = connection_kind::slave;

        _session_id = session_id;
        _name = name;
        _host = host;
        _port = port;

        setup_sockaddr();
    }

    void connection::setup(connection *master_connection) noexcept
    {
        _side = connection_side::remote;
        _kind = connection_kind::slave;

        _session_id = master_connection->session_id();
        _master_connection = master_connection;
    }

    void connection::setup_sockaddr() noexcept
    {
        auto status { uv_ip6_addr(_host.data(), _port, &_addr.sin6) };
        if (status == 0) {
            logdebug("Converted ip6 address to binary representation: %s:%hu, cid: %llu.", _host.data(), _port, _id);
            _version = protocol_domain::v6;
            return;
        }

        status = uv_ip4_addr(_host.data(), _port, &_addr.sin);
        if (status == 0) {
            logdebug("Converted ip4 address to binary representation: %s:%hu, cid: %llu.", _host.data(), _port, _id);
            _version = protocol_domain::v4;
            return;
        }

        logerror("Failed to convert address to binary format.");
    }

}
