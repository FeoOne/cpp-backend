/**
 * @file event_queue.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_EVENT_QUEUE_H
#define ENGINE_EVENT_QUEUE_H

#include "event/event.h"
#include "work/work_loop.h"

namespace engine {

    class event_queue {
    public:
        FW_DECLARE_SMARTPOINTERS(event_queue)
        FW_DELETE_ALL_DEFAULT(event_queue)

        virtual ~event_queue() = default;

        virtual event::sptr dequeue() noexcept = 0;
        bool empty() const noexcept { return _queue.empty(); }

    protected:
        explicit event_queue(const work_loop::sptr& loop) noexcept : _loop { loop } {}

        void push(const event::sptr& e) noexcept;
        event::sptr pop() noexcept;

    private:
        friend class event_recipient;

        std::queue<event::sptr>     _queue;

        /**
         * Called only by event_recipient::enqueue(...)
         * @param e Event to enqueue.
         */
        virtual void enqueue(const event::sptr& e) noexcept = 0;

    };

}

#endif /* ENGINE_EVENT_QUEUE_H */
