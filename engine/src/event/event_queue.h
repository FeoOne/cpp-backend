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
        event_queue();
        virtual ~event_queue();

        void enqueue() noexcept;


    private:

    };

}

#endif /* ENGINE_EVENT_QUEUE_H */
