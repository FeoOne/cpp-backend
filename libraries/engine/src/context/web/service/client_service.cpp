/**
 * @file client_service.cpp
 * @author Feo
 * @date 26/11/2018
 * @brief
 */

#include "context/web/service/client_service.h"

namespace engine {

    client_service::client_service(const stl::setting& config,
                                   task_router *router,
                                   const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _soup_session { nullptr }
    {
    }

    // virtual
    client_service::~client_service()
    {
    }

    void client_service::setup() noexcept
    {
        _soup_session = soup_session_new();
    }

    void client_service::reset() noexcept
    {

    }

}
