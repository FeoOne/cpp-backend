/**
 * @file job_context.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_JOB_CONTEXT_H
#define ENGINE_JOB_CONTEXT_H

#include "core/execution_context.h"
#include "job/job_event_queue.h"

namespace engine {

    class job_context : public execution_context {
    public:
        FW_DECLARE_SMARTPOINTERS(job_context)
        FW_DELETE_ALL_DEFAULT(job_context)

        explicit job_context(const event_queue::sptr& queue,
                             const event_recipient::sptr& recipient,
                             const framework::config_setting::sptr& config) noexcept;
        virtual ~job_context();

    private:
        void _before_run() noexcept final;
        void _after_run() noexcept final;

    };

}

#endif /* ENGINE_JOB_CONTEXT_H */
