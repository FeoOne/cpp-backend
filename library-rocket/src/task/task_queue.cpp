//
// Created by Feo on 16/08/2018.
//

#include "task/task_queue.h"

namespace rocket {

    task_queue::task_queue(const std::string_view& domain) noexcept :
            _domain { domain },
            _queue {}
    {
    }

    void task_queue::push(basic_task *task) noexcept
    {
        _queue.push(task);
    }

    basic_task *task_queue::pop() noexcept
    {
        auto task { _queue.front() };
        _queue.pop();
        return task;
    }

    bool task_queue::is_empty() const noexcept
    {
        return _queue.empty();
    }

}
