/**
 * @file system_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "system/system_loop.h"

namespace rocket {

    system_loop::system_loop(task_queue *queue, const task_handler *handler) noexcept :
            work_loop(queue, handler),
            _should_work { false }
    {
    }

    // virtual
    system_loop::~system_loop()
    {
    }

    // virtual
    void system_loop::start() noexcept
    {
        _should_work.store(true, std::memory_order_relaxed);
        while (_should_work.load(std::memory_order_relaxed)) {
            auto task = get_queue()->dequeue();
            get_task_handler()->handle_task(task);
        }
    }

    // virtual
    void system_loop::stop() noexcept
    {
        bool expected = true;
        do {
            expected = !_should_work.compare_exchange_weak(expected, false);
        } while (expected);
    }

}
