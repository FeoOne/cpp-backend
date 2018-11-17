/**
 * @file network.h
 * @author Feo
 * @date 28/09/2018
 * @brief
 */

#ifndef ENGINE_NETWORK_H
#define ENGINE_NETWORK_H

#include <uv.h>

#include <stl.h>

namespace engine {

    enum class socket_type {
        undefined,
        stream,
        datagram,
    };

    enum class protocol_domain {
        undefined,
        v4,
        v6,
    };

    enum class connection_side {
        undefined,
        local,
        remote,
    };

    enum class connection_kind {
        undefined,
        slave,      // client
        master,     // server
    };

    enum class connection_status {
        disconnecting,
        disconnected,
        connecting,
        connected,
    };

    union socket_address {
        sockaddr        sa;
        sockaddr_in     sin;
        sockaddr_in6    sin6;
    };

    union network_handle {
        uv_handle_t     handle;
        uv_stream_t     stream;
        uv_tcp_t        tcp;
        uv_udp_t        udp;
    };

    union timer_handle {
        uv_handle_t     handle;
        uv_timer_t      timer;
    };

    union poll_handle {
        uv_handle_t     handle;
        uv_poll_t       poll;
    };

    union uv_request {
        uv_req_t        req;
        uv_connect_t    connect;
        uv_shutdown_t   shutdown;
    };

    const char *socket_type_to_str(socket_type protocol) noexcept;
    const char *protocol_domain_to_str(protocol_domain version) noexcept;
    const char *connection_status_to_str(connection_status status) noexcept;

}

#endif /* ENGINE_NETWORK_H */
