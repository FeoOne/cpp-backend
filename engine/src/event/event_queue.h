/**
 * @file event_queue.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_EVENT_QUEUE_H
#define ENGINE_EVENT_QUEUE_H

#include "event/event.h"

namespace engine {

    class event_queue {
    public:
        FW_DECLARE_SMARTPOINTERS(event_queue)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(event_queue)

        virtual ~event_queue() = default;

        virtual event::sptr dequeue() noexcept = 0;

    protected:
        event_queue() = default;

    private:
        friend class event_router;

        virtual void enqueue(const event::sptr& e) noexcept = 0;

    };

}

#endif /* ENGINE_EVENT_QUEUE_H */