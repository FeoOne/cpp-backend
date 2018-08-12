/**
 * @file context_started_event.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_CONTEXT_STARTED_EVENT_H
#define ENGINE_CONTEXT_STARTED_EVENT_H

#include "event/event.h"
#include "core/execution_context.h"

namespace engine {

    class context_did_start_event : public framework::crucial<context_did_start_event, event> {
    public:
        FW_DECLARE_SMARTPOINTERS(context_did_start_event)
        FW_DELETE_ALL_DEFAULT(context_did_start_event)

        explicit context_did_start_event(const execution_context::wptr& context) noexcept : _context { context } {}
        virtual ~context_did_start_event() = default;

        execution_context::wptr context() noexcept { return _context; }

    private:
        execution_context::wptr     _context;

    };

}

#endif /* ENGINE_CONTEXT_STARTED_EVENT_H */
