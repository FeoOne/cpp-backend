/**
 * @file event_recipient.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_EVENT_ROUTE_H
#define ENGINE_EVENT_ROUTE_H

#include "event/event_queue.h"

namespace engine {

    /**
     * @brief Class logic designed in such a way that method
     *        event_recipient::add_route (write to event_recipient::_queues)
     *        is called during initialization from single thread, and
     *        method event_recipient::enqueue (read from event_recipient::_queues)
     *        is called from different threads after initialization.
     *        You must ensure that the collection of routes
     *        does not change during object lifetime.
     */
    class event_recipient {
    public:
        FW_DECLARE_SMARTPOINTERS(event_recipient)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(event_recipient)

        event_recipient();
        ~event_recipient();

        void add_route(event::key_type key, const event_queue::sptr& queue) noexcept;

        void enqueue(const event::sptr& e) noexcept;

    private:
        using queue_map = std::unordered_map<event::key_type, event_queue::sptr>;

        queue_map           _queues;

    };

}

#endif /* ENGINE_EVENT_ROUTE_H */
