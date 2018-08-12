/**
 * @file context_started_event.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_CONTEXT_STARTED_EVENT_H
#define ENGINE_CONTEXT_STARTED_EVENT_H

#include "event/event.h"

namespace engine {

    class context_started_event : public framework::crucial<context_started_event, event> {
    public:
        FW_DECLARE_SMARTPOINTERS(context_started_event)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(context_started_event)

        context_started_event();
        virtual ~context_started_event();

    private:

    };

}

#endif /* ENGINE_CONTEXT_STARTED_EVENT_H */
