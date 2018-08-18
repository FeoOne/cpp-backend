/**
 * @file system_context.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "system/system_loop.h"

#include "system/system_context.h"

using namespace framework;

namespace engine {

    system_context::system_context(const config_setting::sptr& config,
                                   const task_router::sptr& router) noexcept :
            crucial(config, router, system_loop::make_shared(router->get_queue<system_context>()))
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
