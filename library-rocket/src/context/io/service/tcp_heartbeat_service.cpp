/**
 * @file tcp_heartbeat_service.cpp
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#include "context/io/service/tcp_heartbeat_service.h"

namespace rocket {

    tcp_heartbeat_service::tcp_heartbeat_service(const groot::setting& config,
                                                 task_router *router,
                                                 const work_service_delegate *service_delegate) noexcept :
            crucial(config, router, service_delegate)
    {

    }

    // virtual
    tcp_heartbeat_service::~tcp_heartbeat_service()
    {
    }

    // virtual
    void tcp_heartbeat_service::setup() noexcept
    {

    }

    // virtual
    void tcp_heartbeat_service::reset() noexcept
    {

    }

}
