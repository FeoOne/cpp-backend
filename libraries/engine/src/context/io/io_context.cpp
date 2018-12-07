/**
 * @file io_work_context.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include "context/io/io_loop.h"
#include "context/io/service/io_connection_service.h"
#include "context/io/service/tcp_service.h"
#include "context/io/service/udp_service.h"
#include "context/io/service/request_processing_service.h"
#include "context/io/service/response_processing_service.h"
#include "context/io/task/disconnect_connection_task.h"
#include "context/io/task/io_response_task.h"

#include "context/io/io_context.h"

namespace engine {

    io_context::io_context(const stl::setting& config, task_router *router) noexcept :
            crucial(config, router, io_loop::make_unique(router->queue<io_context>(), this))
    {
        add_service(io_connection_service::make_unique(config, router, this));
        add_service(tcp_service::make_unique(config, router, this));
        add_service(udp_service::make_unique(config, router, this));
        add_service(request_processing_service::make_unique(config, router, this));
        add_service(response_processing_service::make_unique(config, router, this));

        EX_BIND_TASK_ROUTE(io_response_task, response_processing_service);
        EX_BIND_TASK_ROUTE(disconnect_connection_task, io_connection_service);
    }

}
