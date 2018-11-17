/**
 * @file connection.cpp
 * @author Feo
 * @date 28/09/2018
 * @brief
 */

#include "context/io/net/network.h"

namespace engine {

    const char *socket_type_to_str(socket_type protocol) noexcept
    {
        static const std::unordered_map<socket_type, std::string_view> values {
                {
                        { socket_type::stream, { "tcp" } },
                        { socket_type::datagram, { "udp" } },
                }
        };
        return values.at(protocol).data();
    }

    const char *protocol_domain_to_str(protocol_domain version) noexcept
    {
        static const std::unordered_map<protocol_domain, std::string_view> values {
                {
                        { protocol_domain::v4, { "ip_v4" } },
                        { protocol_domain::v6, { "ip_v6" } },
                }
        };
        return values.at(version).data();
    }

    const char *connection_status_to_str(connection_status status) noexcept
    {
        static const std::unordered_map<connection_status, std::string_view> values {
                {
                        { connection_status::disconnected, { "disconnected" } },
                        { connection_status::disconnecting, { "disconnecting" } },
                        { connection_status::connected, { "connected" } },
                        { connection_status::connecting, { "connecting" } },
                }
        };
        return values.at(status).data();
    }

}
