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

    union socket_address {
        sockaddr        sa;
        sockaddr_in     sin;
        sockaddr_in6    sin6;
    };

}

#endif /* GROOT_NETWORK_H */
