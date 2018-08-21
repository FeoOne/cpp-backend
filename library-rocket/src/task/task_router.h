//
// Created by Feo on 16/08/2018.
//

#ifndef ROCKET_TASK_ROUTER_H
#define ROCKET_TASK_ROUTER_H

#include "main/rocket_consts.h"
#include "task/task_queue.h"

namespace rocket {

    class task_router {
    public:
        FW_DECLARE_SMARTPOINTERS(task_router)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(task_router)

        task_router();
        ~task_router() = default;

        void add_queue(groot::crucial_key_type context_key, const task_queue::sptr& queue) noexcept;
        task_queue::sptr get_queue(groot::crucial_key_type context_key) const noexcept;

        template<typename Context>
        task_queue::sptr get_queue() const noexcept {
            return get_queue(Context::key());
        }

        void register_route(task::key_type task_key, groot::crucial_key_type context_key) noexcept;

        void enqueue(const task::sptr& task) noexcept;

    private:
        std::array<task_queue::sptr,
                consts::TASK_TYPE_MAX_COUNT>              _queues;
        std::array<groot::crucial_key_type,
                consts::WORK_CONTEXT_TYPE_MAX_COUNT>      _context_keys;

    };

}

#endif /* ROCKET_TASK_ROUTER_H */
