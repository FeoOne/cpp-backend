/**
 * @file job_context.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_JOB_CONTEXT_H
#define ENGINE_JOB_CONTEXT_H

#include "work/work_context.h"

namespace engine {

    class job_context :public framework::crucial<work_context, job_context> {
    public:
        FW_DECLARE_SMARTPOINTERS(job_context)
        FW_DELETE_ALL_DEFAULT(job_context)

        explicit job_context(const framework::config_setting::sptr& config,
                             const task_router::sptr& router) noexcept;
        virtual ~job_context();

    private:
        void setup() noexcept final;
        void reset() noexcept final;

    };

}

#endif /* ENGINE_JOB_CONTEXT_H */
