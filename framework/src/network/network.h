/**
 * @file network.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef FRAMEWORK_NETWORK_H
#define FRAMEWORK_NETWORK_H

#include <netinet/in.h>

namespace framework {

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

#endif /* FRAMEWORK_NETWORK_H */
