/**
 * @file io_context.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ENGINE_IO_CONTEXT_H
#define ENGINE_IO_CONTEXT_H

#include "core/execution_context.h"

namespace engine {

    class io_context : public execution_context {
    public:
        FW_DECLARE_SMARTPOINTERS(io_context)
        FW_DELETE_ALL_DEFAULT(io_context)

        explicit io_context(const event_queue::sptr& queue,
                            const event_recipient::sptr& recipient,
                            const framework::config_setting::sptr& config) noexcept;
        virtual ~io_context();

    private:
        void before_run() noexcept final;
        void after_run() noexcept final;

    };

}

#endif /* ENGINE_IO_CONTEXT_H */
