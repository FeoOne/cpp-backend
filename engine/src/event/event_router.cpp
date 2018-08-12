/**
 * @file event_route.cpp
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#include "event/event_router.h"

namespace engine {

    event_router::event_router() :
            _queues {}
    {

    }

    event_router::~event_router()
    {

    }

    void event_router::add_route(event::key_type key, const event_queue::sptr& queue) noexcept
    {
        auto it = _queues.find(key);
        if (it == _queues.end()) {
            _queues.insert({ key, queue });
        } else {
            logerror("Can't add multiple routes for single event key.");
        }
    }

    void event_router::enqueue(const event::sptr& e) noexcept
    {
        auto it = _queues.find(e->get_key());
        if (it != _queues.end()) {
            it->second->enqueue(e);
        } else {
            logwarn("Missing route for event key %lu.", e->get_key());
        }
    }

}
