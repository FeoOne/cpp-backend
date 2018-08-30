/**
 * @file udp_service.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "io/service/udp_service.h"

namespace rocket {

    udp_service::udp_service(const groot::config_setting::sptr& config,
                             const task_router::sptr& router,
                             const work_service_delegate *service_provider) noexcept :
            crucial(config, router, service_provider)
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
