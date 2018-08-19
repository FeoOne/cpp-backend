/**
 * @file db_context.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "db/db_loop.h"

#include "db/db_context.h"

using namespace framework;

namespace engine {

    db_context::db_context(const config_setting::sptr& config,
                           const task_router::sptr& router) noexcept :
            crucial(config, router, db_loop::make_shared(router->get_queue<db_context>(), this))
    {
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
