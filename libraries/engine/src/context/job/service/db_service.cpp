/**
 * @file db_service.cpp
 * @author Feo
 * @date 10/11/2018
 * @brief
 */

#include "context/db/task/db_response_task.h"

#include "context/job/service/db_service.h"

namespace engine {

    db_service::db_service(const stl::setting& config,
                                           task_router *router,
                                           const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate)
    {
        EX_ASSIGN_TASK_HANDLER(db_response_task, db_service, handle_db_response_task);
    }

    // virtual
    db_service::~db_service()
    {
    }

    // virtual
    void db_service::setup() noexcept
    {

    }

    // virtual
    void db_service::reset() noexcept
    {

    }

    void db_service::handle_db_response_task(engine::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<db_response_task *>(base_task) };
        task->request()->call();
        db_request::destroy(task->request());
    }

}
