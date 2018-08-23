/**
 * @file websocket_service.cpp
 * @author Feo
 * @date 23/08/2018
 * @brief
 */

#include "job/service/websocket_service.h"

namespace quill {

    websocket_service::websocket_service(const groot::config_setting::sptr& config,
                                         const rocket::task_router::sptr& router,
                                         const rocket::work_context_delegate *service_provider) noexcept :
            crucial(config, router, service_provider)
    {

    }

    virtual
    websocket_service::~websocket_service()
    {

    }

    void websocket_service::setup() noexcept
    {

    }

    void websocket_service::reset() noexcept
    {

    }

}
