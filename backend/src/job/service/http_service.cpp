/**
 * @file http_service.cpp
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#include "job/service/http_service.h"

namespace backend {

    http_service::http_service(const framework::config_setting::sptr& config,
                               const engine::task_router::sptr& router,
                               const engine::work_service_provider *service_provider) noexcept :
            crucial(config, router, service_provider)
    {
    }

    // virtual
    http_service::~http_service()
    {
    }

    // virtual
    void http_service::setup() noexcept
    {

    }

    // virtual
    void http_service::reset() noexcept
    {

    }

    // virtual
    void http_service::handle_task(const engine::task::sptr& task) noexcept
    {

    }

}
