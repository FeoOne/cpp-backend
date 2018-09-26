/**
 * @file job_context.cpp
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#include "job/service/io_service.h"
#include "job/service/websocket_service.h"

#include "job/job_context.h"

namespace quill {

    job_context::job_context(const groot::setting& config, rocket::task_router *router) noexcept :
            rocket::job_context(config, router)
    {
        add_service(io_service::make_unique(config, router, this));
        add_service(websocket_service::make_unique(config, router, this));

        RC_BIND_TASK_ROUTE(rocket::message_request_task, io_service);
        RC_BIND_TASK_ROUTE(rocket::ws_incoming_message_task, websocket_service);
    }

}
