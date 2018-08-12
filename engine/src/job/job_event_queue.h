/**
 * @file job_event_queue.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_JOB_EVENT_QUEUE_H
#define ENGINE_JOB_EVENT_QUEUE_H

#include "event/event_queue.h"

namespace engine {

    class job_event_queue final : public event_queue {
    public:
        FW_DECLARE_SMARTPOINTERS(job_event_queue)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(job_event_queue)

        job_event_queue();
        virtual ~job_event_queue() = default;

        event::sptr dequeue() noexcept final;

    private:
        void enqueue(const event::sptr& e) noexcept final;

        std::condition_variable     _cv;
        std::mutex                  _mutex;

    };

}

#endif /* ENGINE_JOB_EVENT_QUEUE_H */
