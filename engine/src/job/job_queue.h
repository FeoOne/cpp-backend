/**
 * @file job_event_queue.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_JOB_EVENT_QUEUE_H
#define ENGINE_JOB_EVENT_QUEUE_H

#include "task/task_queue.h"

namespace engine {

    class job_queue final : public task_queue {
    public:
        FW_DECLARE_SMARTPOINTERS(job_queue)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(job_queue)

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

#endif /* ENGINE_JOB_EVENT_QUEUE_H */
