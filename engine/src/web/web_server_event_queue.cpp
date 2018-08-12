/**
 * @file web_server_event_queue.cpp
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#include "web/web_server_event_queue.h"

namespace engine {

    void web_server_event_queue::enqueue(const event::sptr& e) noexcept
    {

    }

    event::sptr web_server_event_queue::dequeue() noexcept
    {
        return nullptr;
    }

}
