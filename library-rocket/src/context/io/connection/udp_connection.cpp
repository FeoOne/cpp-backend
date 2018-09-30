/**
 * @file udp_connection.cpp
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#include "context/io/connection/udp_connection.h"

namespace rocket {

    udp_connection::udp_connection(u64 id) noexcept :
            connection(id, transport_protocol::udp)
    {
    }



}
