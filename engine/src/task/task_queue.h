//
// Created by Feo on 16/08/2018.
//

#ifndef ENGINE_TASK_QUEUE_H
#define ENGINE_TASK_QUEUE_H

#include <dispatch/dispatch.h>

#include "task/task.h"
#include "task/task_queue_delegate.h"

namespace engine {

    class task_queue {
    public:
        FW_DECLARE_SMARTPOINTERS(task_queue)

        explicit task_queue(const std::string_view& domain) noexcept;

        void set_delegate(const task_queue_delegate::sptr& delegate) noexcept { _delegate = delegate; }

        void push(const task::sptr& task) noexcept;
        task::sptr pop() noexcept;

        bool empty() const noexcept;

    private:
        task_queue_delegate::wptr       _delegate;

        std::queue<task::sptr>          _queue;
        dispatch_queue_t                _dispatch_queue;

    };

}

#endif /* ENGINE_TASK_QUEUE_H */
