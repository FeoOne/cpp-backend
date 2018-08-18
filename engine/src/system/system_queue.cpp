/**
 * @file system_event_queue.cpp
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#include "system/system_queue.h"

namespace engine {

    system_queue::system_queue() :
            task_queue(engine_const::DOMAIN_TASK_QUEUE_SYSTEM)
    {
    }

    // virtual
    void system_queue::enqueue(const task::sptr& task) noexcept
    {

    }

    // virtual
    task::sptr system_queue::dequeue() noexcept
    {
        return nullptr;
    }

    // virtual
    bool system_queue::empty() const noexcept
    {
        return false;
    }

}
