/**
 * @file endpoint.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef FRAMEWORK_ENDPOINT_H
#define FRAMEWORK_ENDPOINT_H

#include "memory/memory.h"
#include "scalar/string.h"
#include "scalar/numeric.h"
#include "network/network.h"

namespace framework {

    class endpoint final {
    public:
        FW_DECLARE_SMARTPOINTERS(endpoint)
        FW_DELETE_ALL_DEFAULT(endpoint)

        explicit endpoint(ip_version version, const std::string_view& host, u16 port) noexcept :
                _version { version },
                _host { host },
                _port { port }
        {}

        ~endpoint() = default;

        ip_version get_version() const noexcept { return _version; }
        const std::string_view& get_host() const noexcept { return _host; }
        u16 get_port() const noexcept { return _port; }

    private:
        ip_version          _version;
        std::string_view    _host;
        u16                 _port;

    };

}

#endif /* FRAMEWORK_ENDPOINT_H */
