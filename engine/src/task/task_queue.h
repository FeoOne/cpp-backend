//
// Created by Feo on 16/08/2018.
//

#ifndef ENGINE_TASK_QUEUE_H
#define ENGINE_TASK_QUEUE_H

#include "task/task.h"
#include "task/task_queue_delegate.h"
#include "main/engine_const.h"

namespace engine {

    class task_queue {
    public:
        FW_DECLARE_SMARTPOINTERS(task_queue)
        FW_DELETE_ALL_DEFAULT(task_queue)

        virtual ~task_queue() = default;

        void set_delegate(const task_queue_delegate::sptr& delegate) noexcept { _delegate = delegate; }

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
        task_queue_delegate::wptr       _delegate;
        std::queue<task::sptr>          _queue;

    };

}

#endif /* ENGINE_TASK_QUEUE_H */
