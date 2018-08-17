//
// Created by Feo on 16/08/2018.
//

#ifndef ENGINE_TASK_RELAY_H
#define ENGINE_TASK_RELAY_H

#include "main/engine_const.h"
#include "task/task_queue.h"
#include "task/task_queue_delegate.h"
#include "work/work_context.h"

namespace engine {

    class task_router {
    public:
        FW_DECLARE_SMARTPOINTERS(task_router)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(task_router)

        task_router();
        ~task_router() = default;

        void add_queue(work_context::key_type key, const task_queue::sptr& queue) noexcept;
        task_queue::sptr get_queue(work_context::key_type key) const noexcept;

        void register_route(task::key_type task_key, work_context::key_type context_key) noexcept;

    private:
        std::array<task_queue::sptr, engine_const::TASK_TYPE_MAX_COUNT>                 _queues;
        std::array<work_context::key_type, engine_const::WORK_CONTEXT_TYPE_MAX_COUNT>   _contexts;

    };

}

#endif /* ENGINE_TASK_RELAY_H */
