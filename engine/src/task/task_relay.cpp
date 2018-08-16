//
// Created by Feo on 16/08/2018.
//

#include "task/task_relay.h"

namespace engine {

    task_relay::task_relay() :
            _queues {}
    {
        _queues.fill(nullptr);
    }

    void task_relay::register_route(task::key_type key, const task_queue::sptr& queue) noexcept
    {
        _queues[key] = queue;
    }

}
