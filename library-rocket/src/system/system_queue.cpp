/**
 * @file system_event_queue.cpp
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#include "system/system_queue.h"

namespace rocket {

    system_queue::system_queue() :
            task_queue(consts::DOMAIN_TASK_QUEUE_SYSTEM),
            _cv {},
            _mutex {}
    {
    }

    // virtual
    void system_queue::enqueue(const task::sptr& task) noexcept
    {
        {
            GR_ULOCK(lock, _mutex);
            push(task);
        }
        _cv.notify_one();
    }

    // virtual
    task::sptr system_queue::dequeue() noexcept
    {
        GR_ULOCK(lock, _mutex);

        _cv.wait(lock, [this]() {
            return !is_empty();
        });

        return pop();
    }

    // virtual
    bool system_queue::empty() const noexcept
    {
        GR_ULOCK(lock, _mutex);
        return is_empty();
    }

}
