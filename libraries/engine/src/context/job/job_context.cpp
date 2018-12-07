/**
 * @file job_context.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "context/job/job_loop.h"
#include "context/job/service/db_service.h"
#include "context/db/task/db_response_task.h"

#include "context/job/job_context.h"

namespace engine {

    job_context::job_context(const stl::setting& config, engine::task_router *router) noexcept :
            crucial(config, router, job_loop::make_unique(router->queue<job_context>(), this))
    {
        add_service(db_service::make_unique(config, router, this));

        EX_BIND_TASK_ROUTE(db_response_task, db_service);
    }

}
