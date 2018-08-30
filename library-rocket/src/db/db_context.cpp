/**
 * @file db_context.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "db/db_loop.h"
#include "db/service/request_service.h"
#include "db/task/db_request_task.h"
#include "db/task/db_response_task.h"

#include "db/db_context.h"

namespace rocket {

    db_context::db_context(const groot::config_setting::sptr& config,
                           const task_router::sptr& router) noexcept :
            crucial(config, router, db_loop::make_shared(router->get_queue<db_context>(), this))
    {
        add_service(request_service::make_shared(get_config(), get_router(), this));
    }

    // virtual
    db_context::~db_context()
    {
    }

    // virtual
    void db_context::setup() noexcept
    {

    }

    // virtual
    void db_context::reset() noexcept
    {

    }

}
