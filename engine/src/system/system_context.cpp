/**
 * @file system_context.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "system/system_context.h"

namespace engine {

    using namespace framework;
    using namespace std::chrono_literals;

    system_context::system_context(const config_setting::sptr& config) noexcept :
            execution_context(config),
            _is_should_work { false }
    {
    }

    // virtual
    system_context::~system_context()
    {
    }

    // virtual
    void system_context::_poll_once() noexcept
    {
        std::this_thread::sleep_for(1s);
    }

    // virtual
    void system_context::_before_execute() noexcept
    {
        _is_should_work = true;
    }

    // virtual
    void system_context::_after_execute() noexcept
    {

    }

    // virtual
    bool system_context::_should_work() const noexcept
    {
        return _is_should_work;
    }

    // virtual
    void system_context::_should_work(bool b) noexcept
    {
        _is_should_work = b;
    }

}
