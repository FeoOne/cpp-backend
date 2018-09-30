/**
 * @file system_context.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "context/system/system_loop.h"
#include "context/system/service/worker_watchdog_service.h"
#include "context/system/task/worker_broken_task.h"

#include "context/system/system_context.h"

namespace engine {

    system_context::system_context(const stl::setting& config, task_router *router) noexcept :
            crucial(config, router, system_loop::make_unique(router->get_queue<system_context>(), this))
    {
        add_service(worker_watchdog_service::make_unique(config, router, this));

        EX_BIND_TASK_ROUTE(worker_broken_task, worker_watchdog_service);
    }

}
