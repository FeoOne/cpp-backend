/**
 * @file db_request_service.cpp
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#include "context/db/task/db_request_task.h"

#include "context/db/service/db_request_service.h"

namespace engine {

    db_request_service::db_request_service(const stl::setting& config,
                                     task_router *router,
                                     const work_service_delegate *delegate) noexcept:
            crucial(config, router, delegate)
    {
        EX_ASSIGN_TASK_HANDLER(db_request_task, db_request_service, handle_db_request_task);
    }

    // virtual
    db_request_service::~db_request_service()
    {

    }

    // virtual
    void db_request_service::setup() noexcept
    {

    }

    // virtual
    void db_request_service::reset() noexcept
    {

    }

    void db_request_service::handle_db_request_task(basic_task *t) noexcept
    {

    }

}
