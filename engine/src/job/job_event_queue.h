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

    class job_event_queue : public event_queue {
    public:
        FW_DECLARE_SMARTPOINTERS(job_event_queue)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(job_event_queue)

        job_event_queue() = default;
        virtual ~job_event_queue() = default;

        void enqueue(const event::sptr& e) noexcept final;
        event::sptr dequeue() noexcept final;

    private:

    };

}

#endif /* ENGINE_JOB_EVENT_QUEUE_H */
