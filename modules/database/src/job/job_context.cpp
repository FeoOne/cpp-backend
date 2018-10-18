/**
 * @file job_context.cpp
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#include "job/service/io_service.h"
#include "job/service/session_service.h"
#include "job/service/message/backend_messaging_service.h"

#include "job/job_context.h"

namespace database {

    job_context::job_context(const stl::setting& config, engine::task_router *router) noexcept :
            engine::job_context(config, router)
    {
        add_service(io_service::make_unique(config, router, this));
        add_service(session_service::make_unique(config, router, this));
        add_service(backend_messaging_service::make_unique(config, router, this));

        EX_BIND_TASK_ROUTE(engine::connection_status_changed_task, io_service);
        EX_BIND_TASK_ROUTE(engine::io_request_task, io_service);
    }

}
