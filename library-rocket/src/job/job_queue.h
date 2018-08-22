/**
 * @file job_event_queue.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ROCKET_JOB_EVENT_QUEUE_H
#define ROCKET_JOB_EVENT_QUEUE_H

#include "task/task_queue.h"

namespace rocket {

    class job_queue final : public task_queue {
    public:
        GR_DECLARE_SMARTPOINTERS(job_queue)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(job_queue)

        job_queue();
        virtual ~job_queue() = default;

        void enqueue(const task::sptr& task) noexcept final;
        task::sptr dequeue() noexcept final;

        bool empty() const noexcept final;

    private:
        std::condition_variable     _cv;
        mutable std::mutex          _mutex;

    };

}

#endif /* ROCKET_JOB_EVENT_QUEUE_H */
