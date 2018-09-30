/**
 * @file connection.cpp
 * @author Feo
 * @date 28/09/2018
 * @brief
 */

#include "context/io/net/network.h"

namespace rocket {

    const char *transport_protocol_to_str(transport_protocol protocol) noexcept
    {
        static const std::unordered_map<transport_protocol, std::string_view> values {
                {
                        { transport_protocol::tcp, { "tcp" } },
                        { transport_protocol::udp, { "udp" } },
                }
        };
        return values.at(protocol).data();
    }

    const char *internet_protocol_version_to_str(internet_protocol_version version) noexcept
    {
        static const std::unordered_map<internet_protocol_version, std::string_view> values {
                {
                        { internet_protocol_version::ip_v4, { "ip_v4" } },
                        { internet_protocol_version::ip_v6, { "ip_v6" } },
                }
        };
        return values.at(version).data();
    }

}
