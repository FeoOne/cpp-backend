/**
 * @file job_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "events/events.h"

#include "job/job_loop.h"

namespace engine {

    job_loop::job_loop(const event_queue::sptr& queue) noexcept :
            execution_loop(queue),
            _is_stopped { true },
            _should_work { false }
    {

    }

    // virtual
    void job_loop::run() noexcept
    {
        _should_work = true;
        _is_stopped = false;

        while (_should_work) {
            auto e = queue()->dequeue();

            // e can be null in case when loop finalize working
            if (static_cast<bool>(e)) {
                logdebug("Dequeued event with key: %lu, name: '%s'.",
                         e->get_key(),
                         event_name_from_key(e->get_key()).data());

                // @todo Implement event processing
            }
        }
        _is_stopped = true;
    }

    // virtual
    void job_loop::stop() noexcept
    {
        _should_work = false;

        // @todo queue->stop
    }

    // virtual
    bool job_loop::stopped() const noexcept
    {
        return _is_stopped;
    }

}
