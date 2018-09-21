/**
 * @file network.cpp
 * @author Feo
 * @date 19/09/2018
 * @brief
 */

#include <unordered_map>
#include <string_view>

#include "network/network.h"

namespace groot {

    const char *network_protocol_to_str(network_protocol proto) noexcept
    {
        static std::unordered_map<network_protocol, std::string_view> values {
            {
                { network_protocol::TCP, { "tcp" } },
                { network_protocol::UDP, { "tcp" } },
            }
        };

        return values[proto].data();
    }

    const char *ip_version_to_str(ip_version ipv) noexcept
    {
        static std::unordered_map<ip_version, std::string_view> values {
            {
                { ip_version::IPV4, { "IPv4" } },
                { ip_version::IPV6, { "IPv6" } },
            }
        };

        return values[ipv].data();
    }

}
