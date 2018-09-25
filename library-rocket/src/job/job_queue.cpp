/**
 * @file job_event_queue.cpp
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#include "job/job_queue.h"

namespace rocket {

    job_queue::job_queue() :
            task_queue(consts::DOMAIN_TASK_QUEUE_JOB),
            _cv {},
            _mutex {}
    {
    }

    // virtual
    void job_queue::enqueue(basic_task *task) noexcept
    {
        {
            GR_ULOCK(lock, _mutex);
            push(task);
        }
        _cv.notify_one();
    }

    // virtual
    basic_task *job_queue::dequeue() noexcept
    {
        GR_ULOCK(lock, _mutex);

        _cv.wait(lock, [this]() {
            return !is_empty();
        });

        return pop();
    }

    // virtual
    bool job_queue::empty() const noexcept
    {
        GR_ULOCK(lock, _mutex);
        return is_empty();
    }

}
