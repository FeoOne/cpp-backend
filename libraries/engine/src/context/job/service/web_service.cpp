//
// Created by Feo on 14/12/2018.
//

#include "context/web/task/http_client_response_task.h"

#include "context/job/service/web_service.h"

namespace engine {

    web_service::web_service(const stl::setting& config,
                             task_router *router,
                             const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate)
    {
        EX_ASSIGN_TASK_HANDLER(http_client_response_task, web_service, handle_http_client_response_task);
    }

    // virtual
    web_service::~web_service()
    {
    }

    // virtual
    void web_service::setup() noexcept
    {

    }

    // virtual
    void web_service::reset() noexcept
    {

    }

    void web_service::handle_http_client_response_task(engine::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<http_client_response_task *>(base_task) };
        task->execute_callback();
    }

}
