/**
 * @file job_context.cpp
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#include "job/service/io_service.h"

#include "job/job_context.h"

namespace strange {

    job_context::job_context(const groot::setting& config, rocket::task_router *router) noexcept :
            rocket::job_context(config, router)
    {
        add_service(io_service::make_unique(config, router, this));

        RC_BIND_TASK_ROUTE(rocket::connection_status_changed_task, io_service);
        RC_BIND_TASK_ROUTE(rocket::io_request_task, io_service);
    }

}
