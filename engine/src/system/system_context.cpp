/**
 * @file system_context.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "system/system_loop.h"

#include "system/system_context.h"

namespace engine {

    using namespace framework;

    system_context::system_context(const event_queue::sptr& queue,
                                   const event_router::sptr& router,
                                   const config_setting::sptr& config) noexcept :
            execution_context(system_loop::make_unique(), queue, router, config)
    {
    }

    // virtual
    system_context::~system_context()
    {
    }

    // virtual
    void system_context::_before_run() noexcept
    {

    }

    // virtual
    void system_context::_after_run() noexcept
    {

    }

}
