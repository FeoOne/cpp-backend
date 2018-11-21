/**
 * @file system_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "context/system/system_loop.h"

namespace engine {

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
        _should_work = true;
        do {
            auto task = queue()->dequeue();
            handler()->handle_task(task);
        } while (_should_work);
    }

    // virtual
    void system_loop::stop() noexcept
    {
        _should_work = false;
//        bool expected = true;
//        do {
//            expected = !_should_work.compare_exchange_weak(expected, false);
//        } while (expected);
    }

}
