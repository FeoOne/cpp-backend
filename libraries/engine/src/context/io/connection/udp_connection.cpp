/**
 * @file udp_connection.cpp
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#include "context/io/connection/udp_connection.h"

namespace engine {

    udp_connection::udp_connection() :
            connection(socket_type::datagram)
    {
    }

}
