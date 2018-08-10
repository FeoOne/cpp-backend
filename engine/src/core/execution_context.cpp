/**
 * @file execution_context.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include "core/execution_context.h"

namespace engine {

    execution_context::execution_context() :
            _services {},
            _should_work { false },
            _should_restart { false },
            _is_stopped { true },
            _thread {}
    {
    }

    execution_context::~execution_context()
    {
    }

    void execution_context::start() noexcept
    {
        if (!stopped()) {
            logerror("Execution context already started.");
            return;
        }

        _thread = std::thread(std::bind(&execution_context::execute, this));
    }

    void execution_context::stop() noexcept
    {

    }

    void execution_context::restart() noexcept
    {

    }

    void execution_context::join() noexcept
    {

    }

    bool execution_context::stopped() const noexcept
    {

    }

    void execution_context::execute() noexcept
    {
        _is_stopped = false;



        _is_stopped = true;
    }

}
