/**
 * @file connection.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "io/connection/connection.h"

namespace rocket {

    connection::connection(groot::network_protocol proto,
                           groot::ip_version version,
                           side side,
                           kind kind) noexcept :
            _connect_request {},
            _shutdown_request {},
            _handle {},
            _proto { proto },
            _version { version },
            _side { side },
            _kind { kind }
    {
    }

}
