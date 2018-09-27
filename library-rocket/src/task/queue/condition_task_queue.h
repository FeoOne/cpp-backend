/**
 * @file condition_task_queue.h
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#ifndef ROCKET_CONDITION_TASK_QUEUE_H
#define ROCKET_CONDITION_TASK_QUEUE_H

#include "task/queue/task_queue.h"

namespace rocket {

    class condition_task_queue final : public task_queue {
    public:
        GR_DECLARE_SMARTPOINTERS(condition_task_queue)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(condition_task_queue)

        condition_task_queue();
        virtual ~condition_task_queue() = default;

        void enqueue(basic_task *task) noexcept final;
        basic_task *dequeue() noexcept final;

        bool empty() const noexcept final;

    private:
        std::condition_variable         _cv;
        mutable std::mutex              _mutex;

    };

}

#endif /* ROCKET_CONDITION_TASK_QUEUE_H */
