//
// Created by Feo on 16/08/2018.
//

#include "task/task_router.h"

namespace engine {

    task_router::task_router() :
            _queues {},
            _context_keys {}
    {
        _queues.fill(nullptr);
        _context_keys.fill(std::numeric_limits<framework::crucial_key_type>::max());
    }

    void task_router::add_queue(framework::crucial_key_type context_key, const task_queue::sptr& queue) noexcept
    {
        _queues[context_key] = queue;
    }

    task_queue::sptr task_router::get_queue(framework::crucial_key_type context_key) const noexcept
    {
        return _queues[context_key];
    }

    void task_router::register_route(task::key_type task_key, framework::crucial_key_type context_key) noexcept
    {
        _context_keys[task_key] = context_key;
    }

    void task_router::enqueue(const task::sptr& task) noexcept
    {
        _queues[_context_keys[task->get_key()]]->enqueue(task);
    }

}
