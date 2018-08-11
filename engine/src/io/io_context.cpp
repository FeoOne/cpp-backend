/**
 * @file io_context.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include "io/io_loop.h"

#include "io/io_context.h"

namespace engine {

    using namespace framework;

    io_context::io_context(const config_setting::sptr& config) noexcept :
            execution_context(io_loop::make_unique(), config)
    {
    }

    // virtual
    io_context::~io_context()
    {
    }

    // virtual
    void io_context::_before_run() noexcept
    {

    }

    // virtual
    void io_context::_after_run() noexcept
    {

    }

}
