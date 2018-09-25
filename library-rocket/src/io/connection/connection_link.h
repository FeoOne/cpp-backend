/**
 * @file connection_link.h
 * @author Feo
 * @date 24/09/2018
 * @brief
 */

#ifndef ROCKET_CONNECTION_LINK_H
#define ROCKET_CONNECTION_LINK_H

#include <groot.h>

namespace rocket {

    /**
     *
     */
    class connection_link final {
    public:
        GR_DELETE_ALL_DEFAULT(connection_link)

        using handle_type = groot::network_handle *;

        explicit connection_link(groot::network_protocol protocol, handle_type handle) noexcept;

    private:


    };

}

#endif /* ROCKET_CONNECTION_LINK_H */
