//
// Created by Feo on 16/08/2018.
//

#include "task/task_router.h"

namespace rocket {

    task_router::task_router() :
            _queues {},
            _context_keys {}
    {
        _context_keys.fill(GR_CRUCIAL_KEY_UNDEFINED);
    }

    void task_router::add_queue(groot::crucial_key_type context_key, task_queue::uptr&& queue) noexcept
    {
        _queues[context_key] = std::move(queue);
    }

    task_queue *task_router::get_queue(groot::crucial_key_type context_key) const noexcept
    {
        return _queues[context_key].get();
    }

    void task_router::assign_route(task::key_type task_key, groot::crucial_key_type context_key) noexcept
    {
        _context_keys[task_key] = context_key;
    }

    void task_router::enqueue(const task::sptr& task) noexcept
    {
        _queues[_context_keys[task->get_key()]]->enqueue(task);
    }

}
