/**
 * @file udp_service.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "context/io/service/udp_service.h"

namespace rocket {

    udp_service::udp_service(const groot::setting& config,
                             task_router *router,
                             const work_service_delegate *service_delegate) noexcept :
            crucial(config, router, service_delegate)
    {
    }

    // virtual
    udp_service::~udp_service()
    {
    }

    void udp_service::setup() noexcept
    {

    }

    void udp_service::reset() noexcept
    {

    }

}
