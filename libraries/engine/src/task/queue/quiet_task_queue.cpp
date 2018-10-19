/**
 * @file quiet_task_queue.cpp
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#include "task/queue/quiet_task_queue.h"

namespace engine {

    quiet_task_queue::quiet_task_queue() :
            _mutex {},
            _notify_fn {}
    {
    }

    // virtual
//    quiet_task_queue::~quiet_task_queue()
//    {
//    }

    // virtual
    void quiet_task_queue::enqueue(basic_task *task) noexcept
    {
        do {
            STL_UNIQUE_LOCK(lock, _mutex);
            _queue.push(task);
        } while (false);

        if (_notify_fn) {
            _notify_fn();
        }
    }

    // virtual
    basic_task *quiet_task_queue::dequeue() noexcept
    {
        STL_UNIQUE_LOCK(lock, _mutex);
        auto task { _queue.front() };
        _queue.pop();
        return task;
    }

    // virtual
    bool quiet_task_queue::empty() const noexcept
    {
        STL_UNIQUE_LOCK(lock, _mutex);
        return _queue.empty();
    }

}
