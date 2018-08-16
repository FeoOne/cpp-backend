/**
 * @file context_started_event.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_CONTEXT_STARTED_EVENT_H
#define ENGINE_CONTEXT_STARTED_EVENT_H

#include "event/event.h"
#include "work/worker.h"

namespace engine {

    class context_did_start_event : public framework::crucial<event, context_did_start_event> {
    public:
        FW_DECLARE_SMARTPOINTERS(context_did_start_event)
        FW_DELETE_ALL_DEFAULT(context_did_start_event)

        explicit context_did_start_event(const worker::wptr& context) noexcept : _context { context } {}
        virtual ~context_did_start_event() = default;

        worker::wptr get_context() noexcept { return _context; }

    private:
        worker::wptr     _context;

    };

}

#endif /* ENGINE_CONTEXT_STARTED_EVENT_H */
