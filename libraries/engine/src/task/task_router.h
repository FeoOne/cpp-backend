//
// Created by Feo on 16/08/2018.
//

#ifndef ENGINE_TASK_ROUTER_H
#define ENGINE_TASK_ROUTER_H

#include "main/engine_consts.h"
#include "task/queue/task_queue.h"

namespace engine {

    class task_router {
    public:
        STL_DECLARE_SMARTPOINTERS(task_router)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(task_router)

        task_router();
        ~task_router() = default;

        void add_queue(stl::crucial_key_type context_key, task_queue::uptr&& queue) noexcept;
        task_queue *get_queue(stl::crucial_key_type context_key) const noexcept;

        template<typename T>
        task_queue *get_queue() const noexcept {
            return get_queue(T::key());
        }

        void assign_route(basic_task::key_type task_key, stl::crucial_key_type context_key) noexcept;

        void enqueue(basic_task *task) noexcept;

    private:
        std::array<task_queue::uptr, EX_WORK_CONTEXT_TYPE_MAX_KEY_COUNT>    _queues;
        std::array<stl::crucial_key_type, basic_task::MAX_KEY>            _context_keys;

    };

}

#endif /* ENGINE_TASK_ROUTER_H */
