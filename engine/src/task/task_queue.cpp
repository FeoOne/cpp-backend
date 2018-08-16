//
// Created by Feo on 16/08/2018.
//

#include "task/task_queue.h"

namespace engine {

    task_queue::task_queue(const std::string_view& domain) noexcept :
            _delegate {}
    {
        _dispatch_queue = dispatch_queue_create(domain.data(), nullptr);
    }

    void task_queue::push(const task::sptr& task) noexcept
    {
        dispatch_async(_dispatch_queue, ^{
            _queue.push(task);
            if (auto delegate = _delegate.lock()) {
                delegate->on_task_added();
            }
        });
    }

    task::sptr task_queue::pop() noexcept
    {
        task::sptr task;
        dispatch_sync(_dispatch_queue, ^{
            task = _queue.front();
            _queue.pop();
        });
        return task;
    }

    bool task_queue::empty() const noexcept
    {
        return _queue.empty();
    }

}
