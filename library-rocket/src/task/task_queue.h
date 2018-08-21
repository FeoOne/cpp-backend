//
// Created by Feo on 16/08/2018.
//

#ifndef ROCKET_TASK_QUEUE_H
#define ROCKET_TASK_QUEUE_H

#include "task/task.h"
#include "main/rocket_consts.h"

namespace rocket {

    class task_queue {
    public:
        FW_DECLARE_SMARTPOINTERS(task_queue)
        FW_DELETE_ALL_DEFAULT(task_queue)

        virtual ~task_queue() = default;

        virtual void enqueue(const task::sptr& task) noexcept = 0;
        virtual task::sptr dequeue() noexcept = 0;

        virtual bool empty() const noexcept = 0;

    protected:
        explicit task_queue(const std::string_view& domain) noexcept;

        void push(const task::sptr& task) noexcept;
        task::sptr pop() noexcept;

        bool is_empty() const noexcept;

    private:
        std::string_view                _domain;
        std::queue<task::sptr>          _queue;

    };

}

#endif /* ROCKET_TASK_QUEUE_H */
