/**
 * @file system_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "system/system_loop.h"

namespace engine {

    using namespace std::chrono_literals;

    system_loop::system_loop(const event_queue::sptr& queue) noexcept :
            execution_loop(queue),
            _is_stopped { true },
            _should_work { false }
    {

    }

    // virtual
    system_loop::~system_loop()
    {
    }

    // virtual
    void system_loop::run() noexcept
    {
        _should_work = true;
        _is_stopped = false;
        while (_should_work) {
            std::this_thread::sleep_for(1s);
        }
        _is_stopped = true;
    }

    // virtual
    void system_loop::stop() noexcept
    {
        _should_work = false;
    }

    // virtual
    bool system_loop::stopped() const noexcept
    {
        return _is_stopped;
    }

}
