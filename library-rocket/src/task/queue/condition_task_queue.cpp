/**
 * @file condition_task_queue.cpp
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#include "task/queue/condition_task_queue.h"

namespace rocket {

    condition_task_queue::condition_task_queue() :
            _cv {},
            _mutex {}
    {
    }

    // virtual
//    condition_task_queue::~condition_task_queue()
//    {
//    }

    // virtual
    void condition_task_queue::enqueue(basic_task *task) noexcept
    {
        {
            GR_UNIQUE_LOCK(lock, _mutex);
            _queue.push(task);
        }

        _cv.notify_one();
    }

    // virtual
    basic_task *condition_task_queue::dequeue() noexcept
    {
        GR_UNIQUE_LOCK(lock, _mutex);

        _cv.wait(lock, [this]() {
            return !_queue.empty();
        });

        auto task { _queue.front() };
        _queue.pop();
        return task;
    }

    // virtual
    bool condition_task_queue::empty() const noexcept
    {
        GR_UNIQUE_LOCK(lock, _mutex);
        return _queue.empty();
    }

}
