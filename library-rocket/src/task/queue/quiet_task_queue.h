/**
 * @file quiet_task_queue.h
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#ifndef ROCKET_QUIET_TASK_QUEUE_H
#define ROCKET_QUIET_TASK_QUEUE_H

#include "task/queue/task_queue.h"

namespace rocket {

    class quiet_task_queue final : public task_queue {
    public:
        GR_DECLARE_SMARTPOINTERS(quiet_task_queue)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(quiet_task_queue)

        quiet_task_queue();
        virtual ~quiet_task_queue() = default;

        void enqueue(basic_task *task) noexcept final;
        basic_task *dequeue() noexcept final;

        bool empty() const noexcept final;

    private:
        mutable std::timed_mutex        _mutex;

    };

}

#endif /* ROCKET_QUIET_TASK_QUEUE_H */
