/**
 * @file system_event_queue.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_SYSTEM_EVENT_QUEUE_H
#define ENGINE_SYSTEM_EVENT_QUEUE_H

#include "event/event_queue.h"

namespace engine {

    class system_event_queue : public event_queue {
    public:
        FW_DECLARE_SMARTPOINTERS(system_event_queue)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(system_event_queue)

        system_event_queue() = default;
        virtual ~system_event_queue() = default;

        void enqueue(const event::sptr& e) noexcept final;
        event::sptr dequeue() noexcept final;

    private:

    };

}

#endif /* ENGINE_SYSTEM_EVENT_QUEUE_H */
