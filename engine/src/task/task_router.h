//
// Created by Feo on 16/08/2018.
//

#ifndef ENGINE_TASK_ROUTER_H
#define ENGINE_TASK_ROUTER_H

#include "main/engine_const.h"
#include "task/task_queue.h"
#include "task/task_queue_delegate.h"

namespace engine {

    class task_router {
    public:
        FW_DECLARE_SMARTPOINTERS(task_router)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(task_router)

        task_router();
        ~task_router() = default;

        void add_queue(framework::crucial_key_type context_key, const task_queue::sptr& queue) noexcept;
        task_queue::sptr get_queue(framework::crucial_key_type context_key) const noexcept;

        template<typename Context>
        task_queue::sptr get_queue() const noexcept {
            return get_queue(Context::key());
        }

        void register_route(task::key_type task_key, framework::crucial_key_type context_key) noexcept;

        void enqueue(const task::sptr& task) noexcept;

    private:
        std::array<task_queue::sptr,
                engine_const::TASK_TYPE_MAX_COUNT>              _queues;
        std::array<framework::crucial_key_type,
                engine_const::WORK_CONTEXT_TYPE_MAX_COUNT>      _context_keys;

    };

}

#endif /* ENGINE_TASK_ROUTER_H */
