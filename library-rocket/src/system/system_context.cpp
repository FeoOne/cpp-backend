/**
 * @file system_context.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "system/system_loop.h"

#include "system/system_context.h"

namespace rocket {

    system_context::system_context(const groot::config_setting::sptr& config,
                                   const task_router::sptr& router) noexcept :
            crucial(config, router, system_loop::make_shared(router->get_queue<system_context>(), this))
    {
    }

    // virtual
    system_context::~system_context()
    {
    }

    // virtual
    void system_context::setup() noexcept
    {

    }

    // virtual
    void system_context::reset() noexcept
    {

    }

}
