/**
 * @file io_work_context.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include "io/io_loop.h"

#include "io/io_context.h"

using namespace framework;

namespace engine {

    io_context::io_context(const config_setting::sptr& config,
                           const task_router::sptr& router) noexcept :
            crucial(config, router, io_loop::make_shared(router->get_queue<io_context>(), this))
    {
    }

    // virtual
    io_context::~io_context()
    {
    }

    // virtual
    void io_context::setup() noexcept
    {

    }

    // virtual
    void io_context::reset() noexcept
    {

    }

}
