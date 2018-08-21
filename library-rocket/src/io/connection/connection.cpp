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
                           side_t side,
                           kind_t kind) noexcept :
            _handle {},
            _proto { proto },
            _version { version },
            _side { side },
            _kind { kind }
    {
    }

}
