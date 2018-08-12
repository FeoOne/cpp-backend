/**
 * @file web_server_event_queue.cpp
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#include "web/web_server_event_queue.h"

namespace engine {

    // vitual
    void web_server_event_queue::enqueue(const event::sptr& e) noexcept
    {
        std::unique_lock<std::timed_mutex> lock(_mutex);
        push(e);
    }

    // vitual
    event::sptr web_server_event_queue::dequeue() noexcept
    {
        std::unique_lock<std::timed_mutex> lock(_mutex);
        return empty() ? nullptr : pop();
    }

}
