//
// Created by Feo on 16/08/2018.
//

#ifndef ENGINE_TASK_QUEUE_H
#define ENGINE_TASK_QUEUE_H

#include "task/basic_task.h"

namespace engine {

    class task_queue {
    public:
        STL_DECLARE_SMARTPOINTERS(task_queue)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(task_queue)

        virtual ~task_queue() = default;

        virtual void enqueue(basic_task *task) noexcept = 0;
        virtual void enqueue(std::vector<basic_task *>&& tasks) noexcept = 0;
        virtual basic_task *dequeue() noexcept = 0;

        virtual bool empty() const noexcept = 0;

    protected:
        std::queue<basic_task *>        _queue;

        task_queue() : _queue {} {}

    };

}

#endif /* ENGINE_TASK_QUEUE_H */
