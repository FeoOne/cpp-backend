/**
 * @file system_event_queue.cpp
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#include "system/system_event_queue.h"

namespace engine {

    // vitual
    void system_event_queue::enqueue(const event::sptr& e) noexcept
    {

    }

    // vitual
    event::sptr system_event_queue::dequeue() noexcept
    {
        return nullptr;
    }

}
