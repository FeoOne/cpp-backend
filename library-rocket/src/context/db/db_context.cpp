/**
 * @file db_context.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "context/db/db_loop.h"
#include "context/db/service/connection_service.h"
#include "context/db/service/request_service.h"
#include "context/db/task/db_request_task.h"
#include "context/db/task/db_response_task.h"

#include "context/db/db_context.h"

namespace rocket {

    db_context::db_context(const groot::setting& config, task_router *router) noexcept :
            crucial(config, router, db_loop::make_unique(router->get_queue<db_context>(), this))
    {
        add_service(connection_service::make_unique(config, router, this));
        add_service(request_service::make_unique(config, router, this));

        RC_BIND_TASK_ROUTE(db_request_task, request_service);
    }

}
