//
// Created by Feo on 16/08/2018.
//

#include "task/task_router.h"

namespace engine {

    task_router::task_router() :
            _queues {},
            _contexts {}
    {
        _queues.fill(nullptr);
        _contexts.fill(std::numeric_limits<work_context::key_type>::max());
    }

    void task_router::add_queue(work_context::key_type key, const task_queue::sptr& queue) noexcept
    {
        _queues[key] = queue;
    }

    task_queue::sptr task_router::get_queue(work_context::key_type key) const noexcept
    {
        return _queues[key];
    }

    void task_router::register_route(task::key_type task_key, work_context::key_type context_key) noexcept
    {
        _contexts[task_key] = context_key;
    }

}
