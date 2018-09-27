/**
 * @file quiet_task_queue.cpp
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#include "task/queue/quiet_task_queue.h"

namespace rocket {

    quiet_task_queue::quiet_task_queue() :
            _mutex {}
    {
    }

    // virtual
//    quiet_task_queue::~quiet_task_queue()
//    {
//    }

    // virtual
    void quiet_task_queue::enqueue(basic_task *task) noexcept
    {
        GR_UNIQUE_LOCK(lock, _mutex);
        _queue.push(task);
    }

    // virtual
    basic_task *quiet_task_queue::dequeue() noexcept
    {
        GR_UNIQUE_LOCK(lock, _mutex);
        auto task { _queue.front() };
        _queue.pop();
        return task;
    }

    // virtual
    bool quiet_task_queue::empty() const noexcept
    {
        GR_UNIQUE_LOCK(lock, _mutex);
        return _queue.empty();
    }

}
