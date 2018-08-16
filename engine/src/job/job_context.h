/**
 * @file job_context.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_JOB_CONTEXT_H
#define ENGINE_JOB_CONTEXT_H

#include "work/worker.h"
#include "job/job_event_queue.h"

namespace engine {

    class job_context : public worker {
    public:
        FW_DECLARE_SMARTPOINTERS(job_context)
        FW_DELETE_ALL_DEFAULT(job_context)

        explicit job_context(const event_queue::sptr& queue,
                             const event_recipient::sptr& recipient,
                             const framework::config_setting::sptr& config) noexcept;
        virtual ~job_context();

    private:
        void before_run() noexcept final;
        void after_run() noexcept final;

    };

}

#endif /* ENGINE_JOB_CONTEXT_H */
