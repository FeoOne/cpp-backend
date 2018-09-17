/**
 * @file webserver_context.cpp
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#include "web/webserver_loop.h"
#include "web/service/webserver_service.h"
#include "web/service/http_service.h"
#include "web/service/websocket_service.h"
#include "web/task/http_response_task.h"
#include "web/task/ws_outgoing_message_task.h"

#include "web/webserver_context.h"

namespace rocket {

    webserver_context::webserver_context(const groot::setting& config, task_router *router) noexcept :
            crucial(config, router, webserver_loop::make_unique(router->get_queue<webserver_context>(), this))
    {
        add_service(webserver_service::make_unique(get_config(), get_router(), this));
        add_service(http_service::make_unique(get_config(), get_router(), this));
        add_service(websocket_service::make_unique(get_config(), get_router(), this));

        RC_BIND_TASK_ROUTE(http_response_task, http_service);
        RC_BIND_TASK_ROUTE(ws_outgoing_message_task, websocket_service);
    }

}
