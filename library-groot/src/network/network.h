/**
 * @file network.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef GROOT_NETWORK_H
#define GROOT_NETWORK_H

#include <netinet/in.h>

namespace groot {

    enum class network_protocol {
        TCP,
        UDP,
    };

    enum class ip_version {
        IPV4,
        IPV6,
    };

    enum class connection_side {
        LOCAL,
        REMOTE,
    };

    enum class connection_kind {
        CLIENT,
        SERVER,
    };

    union socket_address {
        sockaddr        sa;
        sockaddr_in     sin;
        sockaddr_in6    sin6;
    };

    const char *network_protocol_to_str(network_protocol proto) noexcept;
    const char *ip_version_to_str(ip_version ipv) noexcept;

}

#endif /* GROOT_NETWORK_H */
