//
// Created by Feo on 16/08/2018.
//

#ifndef ROCKET_TASK_ROUTER_H
#define ROCKET_TASK_ROUTER_H

#include "main/rocket_consts.h"
#include "task/queue/task_queue.h"

namespace rocket {

    class task_router {
    public:
        GR_DECLARE_SMARTPOINTERS(task_router)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(task_router)

        task_router();
        ~task_router() = default;

        void add_queue(groot::crucial_key_type context_key, task_queue::uptr&& queue) noexcept;
        task_queue *get_queue(groot::crucial_key_type context_key) const noexcept;

        template<typename T>
        task_queue *get_queue() const noexcept {
            return get_queue(T::key());
        }

        void assign_route(basic_task::key_type task_key, groot::crucial_key_type context_key) noexcept;

        void enqueue(basic_task *task) noexcept;

    private:
        std::array<task_queue::uptr, RC_WORK_CONTEXT_TYPE_MAX_KEY_COUNT>    _queues;
        std::array<groot::crucial_key_type, basic_task::MAX_KEY>            _context_keys;

    };

}

#endif /* ROCKET_TASK_ROUTER_H */
