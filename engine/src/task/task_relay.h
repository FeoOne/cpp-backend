//
// Created by Feo on 16/08/2018.
//

#ifndef ENGINE_TASK_RELAY_H
#define ENGINE_TASK_RELAY_H

#include "main/engine_const.h"
#include "task/task_queue.h"

namespace engine {

    class task_relay {
    public:
        FW_DECLARE_SMARTPOINTERS(task_relay)

        task_relay();
        ~task_relay() = default;

        void register_route(task::key_type key, const task_queue::sptr& queue) noexcept;

    private:
        std::array<task_queue::sptr, engine_const::TASK_TYPE_MAX_COUNT>     _queues;

    };

}

#endif /* ENGINE_TASK_RELAY_H */
