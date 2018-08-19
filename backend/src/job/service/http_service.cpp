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
        add_task_handler(engine::http_request_task::key(),
                         std::bind(&http_service::handle_http_request_task, this, std::placeholders::_1));
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

    void http_service::handle_http_request_task(const engine::task::sptr& t) noexcept
    {
        auto task = std::static_pointer_cast<engine::http_request_task>(t);
        auto response = engine::http_response::make_shared(task->get_request(), SoupStatus::SOUP_STATUS_OK);
        get_router()->enqueue(engine::http_response_task::make_shared(response));
    }

}
