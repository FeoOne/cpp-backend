/**
 * @file web_server_event_queue.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_WEB_SERVER_EVENT_QUEUE_H
#define ENGINE_WEB_SERVER_EVENT_QUEUE_H

#include "event/event_queue.h"

namespace engine {

    class web_server_event_queue : public event_queue {
    public:
        FW_DECLARE_SMARTPOINTERS(web_server_event_queue)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(web_server_event_queue)

        web_server_event_queue() = default;
        virtual ~web_server_event_queue() = default;

        event::sptr dequeue() noexcept final;

    private:
        std::timed_mutex        _mutex;

        void enqueue(const event::sptr& e) noexcept final;

    };

}

#endif /* ENGINE_WEB_SERVER_EVENT_QUEUE_H */
