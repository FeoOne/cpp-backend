/**
 * @file io_work_context.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include "context/io/io_loop.h"
#include "context/io/service/connection_service.h"
#include "context/io/service/tcp_service.h"
#include "context/io/service/udp_service.h"
#include "context/io/service/request_processing_service.h"
#include "context/io/service/response_processing_service.h"
#include "context/io/task/io_response_task.h"

#include "context/io/io_context.h"

namespace rocket {

    io_context::io_context(const groot::setting& config, task_router *router) noexcept :
            crucial(config, router, io_loop::make_unique(router->get_queue<io_context>(), this))
    {
        add_service(connection_service::make_unique(config, router, this));
        add_service(tcp_service::make_unique(config, router, this));
        add_service(udp_service::make_unique(config, router, this));
        add_service(request_processing_service::make_unique(config, router, this));
        add_service(response_processing_service::make_unique(config, router, this));

        RC_BIND_TASK_ROUTE(io_response_task, response_processing_service);
    }

}
