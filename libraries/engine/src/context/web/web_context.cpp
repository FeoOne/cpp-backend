/**
 * @file web_context.cpp
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#include "context/web/web_loop.h"
#include "context/web/service/server_service.h"
#include "context/web/service/http_service.h"
#include "context/web/service/ws_service.h"
#include "context/web/task/http_response_task.h"
#include "context/web/task/ws_response_task.h"
#include "context/web/task/ws_disconnect_task.h"

#include "context/web/web_context.h"

namespace engine {

    web_context::web_context(const stl::setting& config, task_router *router) noexcept :
            crucial(config, router, web_loop::make_unique(router->get_queue<web_context>(), this))
    {
        add_service(server_service::make_unique(config, router, this));
        add_service(http_service::make_unique(config, router, this));
        add_service(ws_service::make_unique(config, router, this));

        EX_BIND_TASK_ROUTE(http_response_task, http_service);
        EX_BIND_TASK_ROUTE(ws_response_task, ws_service);
        EX_BIND_TASK_ROUTE(ws_disconnect_task, ws_service);
    }

}
