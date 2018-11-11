/**
 * @file worker_watchdog_service.cpp
 * @author Feo
 * @date 14/09/2018
 * @brief
 */

#include "context/system/task/worker_broken_task.h"

#include "context/system/service/worker_watchdog_service.h"

namespace engine {

    worker_watchdog_service::worker_watchdog_service(const stl::setting& config,
                                                     task_router *router,
                                                     const work_service_delegate *delegate) noexcept:
            crucial(config, router, delegate)
    {
        EX_ASSIGN_TASK_HANDLER(worker_broken_task, worker_watchdog_service, handle_worker_broken_task);
    }

    // virtual
    worker_watchdog_service::~worker_watchdog_service()
    {
    }

    // virtual
    void worker_watchdog_service::setup() noexcept
    {

    }

    // virtual
    void worker_watchdog_service::reset() noexcept
    {

    }

    void worker_watchdog_service::handle_worker_broken_task(basic_task *t) noexcept
    {

    }

}
