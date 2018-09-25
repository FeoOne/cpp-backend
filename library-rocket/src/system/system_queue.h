/**
 * @file system_queue.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ROCKET_SYSTEM_QUEUE_H
#define ROCKET_SYSTEM_QUEUE_H

#include "task/task_queue.h"

namespace rocket {

    class system_queue final : public task_queue {
    public:
        GR_DECLARE_SMARTPOINTERS(system_queue)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(system_queue)

        system_queue();
        virtual ~system_queue() = default;

        void enqueue(basic_task *task) noexcept final;
        basic_task *dequeue() noexcept final;

        bool empty() const noexcept final;

    private:
        std::condition_variable     _cv;
        mutable std::mutex          _mutex;

    };

}

#endif /* ROCKET_SYSTEM_QUEUE_H */
