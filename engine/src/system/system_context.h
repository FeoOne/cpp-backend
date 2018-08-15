/**
 * @file system_context.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef ENGINE_SYSTEM_CONTEXT_H
#define ENGINE_SYSTEM_CONTEXT_H

#include "core/execution_context.h"
#include "system/system_event_queue.h"

namespace engine {

    class system_context : public execution_context {
    public:
        FW_DECLARE_SMARTPOINTERS(system_context)
        FW_DELETE_ALL_DEFAULT(system_context)

        explicit system_context(const event_queue::sptr& queue,
                                const event_recipient::sptr& recipient,
                                const framework::config_setting::sptr& config) noexcept;
        virtual ~system_context();

    private:
        void before_run() noexcept final;
        void after_run() noexcept final;

    };

}

#endif /* ENGINE_SYSTEM_CONTEXT_H */
