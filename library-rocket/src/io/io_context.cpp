/**
 * @file io_work_context.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include "io/io_loop.h"
#include "io/service/tcp_service.h"
#include "io/service/udp_service.h"
#include "io/service/response_processing_service.h"
#include "io/service/request_processing_service.h"
#include "io/task/message_response_task.h"
#include "io/task/close_connection_task.h"

#include "io/io_context.h"

namespace rocket {

    io_context::io_context(const groot::setting& config, task_router *router) noexcept :
            crucial(config, router, io_loop::make_unique(router->get_queue<io_context>(), this))
    {
        add_service(tcp_service::make_unique(get_config(), get_router(), this));
        add_service(udp_service::make_unique(get_config(), get_router(), this));
        add_service(response_processing_service::make_unique(get_config(), get_router(), this));
        add_service(request_processing_service::make_unique(get_config(), get_router(), this));

        //RC_BIND_TASK_ROUTE(close_connection_task, );
        RC_BIND_TASK_ROUTE(message_response_task, response_processing_service);
    }

}
