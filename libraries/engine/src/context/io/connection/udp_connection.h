/**
 * @file udp_connection.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ENGINE_UDP_CONNECTION_H
#define ENGINE_UDP_CONNECTION_H

#include "context/io/connection/connection.h"

namespace engine {

    class udp_connection final : public connection {
    public:
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(udp_connection)

        udp_connection();
        virtual ~udp_connection() = default;

        bool open(uv_loop_t *loop, void *data) noexcept final {}

        bool start(uv_alloc_cb alloc_cb, uv_read_cb read_cb) noexcept final {}
        void stop() noexcept final {}

    private:

    };

}

#endif /* ENGINE_UDP_CONNECTION_H */
