/**
 * @file network.h
 * @author Feo
 * @date 28/09/2018
 * @brief
 */

#ifndef ROCKET_NETWORK_H
#define ROCKET_NETWORK_H

#include <uv.h>

#include <groot.h>

namespace rocket {

    enum class transport_protocol {
        tcp,
        udp,
    };

    enum class internet_protocol_version {
        undefined,
        ip_v4,
        ip_v6,
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

    union uv_request {
        uv_req_t        req;
        uv_connect_t    connect;
    };

    union timer_handle {
        uv_handle_t     handle;
        uv_timer_t      timer;
    };

    const char *transport_protocol_to_str(transport_protocol protocol) noexcept;
    const char *internet_protocol_version_to_str(internet_protocol_version version) noexcept;

}

#endif /* ROCKET_NETWORK_H */
