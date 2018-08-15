/**
 * @file job_event_queue.cpp
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#include "job/job_event_queue.h"

namespace engine {

    job_event_queue::job_event_queue(const execution_loop::sptr& loop) :
            event_queue(loop),
            _cv {},
            _mutex {}
    {
    }

    // vitual
    void job_event_queue::enqueue(const event::sptr& e) noexcept
    {
        {
            std::unique_lock<std::mutex> lock(_mutex);
            push(e);
        }

        _cv.notify_one();
    }

    // vitual
    event::sptr job_event_queue::dequeue() noexcept
    {
        std::unique_lock<std::mutex> lock(_mutex);

        _cv.wait(lock, [this]() {
            return !empty();
        });

        return pop();
    }

}
