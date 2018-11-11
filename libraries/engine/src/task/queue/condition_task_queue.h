/**
 * @file condition_task_queue.h
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#ifndef ENGINE_CONDITION_TASK_QUEUE_H
#define ENGINE_CONDITION_TASK_QUEUE_H

#include "task/queue/task_queue.h"

namespace engine {

    class condition_task_queue final : public task_queue {
    public:
        STL_DECLARE_SMARTPOINTERS(condition_task_queue)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(condition_task_queue)

        condition_task_queue();
        virtual ~condition_task_queue() = default;

        void enqueue(basic_task *task) noexcept final;
        void enqueue(std::vector<basic_task *>&& tasks) noexcept final;
        basic_task *dequeue() noexcept final;

        bool empty() const noexcept final;

    private:
        std::condition_variable         _cv;
        mutable std::mutex              _mutex;

    };

}

#endif /* ENGINE_CONDITION_TASK_QUEUE_H */
