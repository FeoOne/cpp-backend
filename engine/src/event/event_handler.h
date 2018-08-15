/**
 * @file event_handler.h
 * @author Feo
 * @date 14/08/2018
 * @brief
 */

#ifndef ENGINE_EVENT_HANDLER_H
#define ENGINE_EVENT_HANDLER_H

#include "event/event.h"

namespace engine {

    class event_handler {
    public:
        FW_DECLARE_SMARTPOINTERS(event_handler)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(event_handler)

        virtual ~event_handler() = default;

        virtual std::vector<event::sptr> operator()(const event::sptr& eve) noexcept = 0;

    protected:
        event_handler() = default;

    };

}

#endif /* ENGINE_EVENT_HANDLER_H */
