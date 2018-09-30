/**
 * @file udp_connection.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ROCKET_UDP_CONNECTION_H
#define ROCKET_UDP_CONNECTION_H

#include "context/io/connection/connection.h"

namespace rocket {

    class udp_connection final : public connection {
    public:
        GR_DELETE_ALL_DEFAULT(udp_connection)

        virtual ~udp_connection() = default;

        bool open(uv_loop_t *loop, void *data) noexcept final {}

        bool start(uv_alloc_cb alloc_cb, uv_read_cb read_cb) noexcept final {}
        void stop() noexcept final {}

    private:
        template<typename>
        friend class connection_manager;

        explicit udp_connection(u64 id) noexcept;

    };

}

#endif /* ROCKET_UDP_CONNECTION_H */
