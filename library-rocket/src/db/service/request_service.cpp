/**
 * @file request_service.cpp
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#include "db/task/db_request_task.h"

#include "db/service/request_service.h"

namespace rocket {

    request_service::request_service(const groot::config_setting::sptr& config,
                                     const task_router::sptr& router,
                                     const work_service_delegate *service_provider) noexcept:
            crucial(config, router, service_provider)
    {
        RC_BIND_TASK_HANDLER(db_request_task, request_service, handle_db_request_task);
    }

    // virtual
    request_service::~request_service()
    {

    }

    // virtual
    void request_service::setup() noexcept
    {

    }

    // virtual
    void request_service::reset() noexcept
    {

    }

    void request_service::handle_db_request_task(const task::sptr& t) noexcept
    {

    }

}
