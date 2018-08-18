/**
 * @file system_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "system/system_loop.h"

namespace engine {

    using namespace std::chrono_literals;

    system_loop::system_loop(const task_queue::sptr& queue) noexcept :
            work_loop(queue)
    {
    }

    // virtual
    system_loop::~system_loop()
    {
    }

    // virtual
    void system_loop::start() noexcept
    {
        while (true) {
            std::this_thread::sleep_for(1s);
        }
    }

    // virtual
    void system_loop::stop() noexcept
    {

    }

}
