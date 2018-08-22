/**
 * @file job_context.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ROCKET_JOB_CONTEXT_H
#define ROCKET_JOB_CONTEXT_H

#include "work/work_context.h"

namespace rocket {

    class job_context : public groot::crucial<work_context, job_context> {
    public:
        GR_DECLARE_SMARTPOINTERS(job_context)
        GR_DELETE_ALL_DEFAULT(job_context)

        virtual ~job_context() = default;

    protected:
        explicit job_context(const groot::config_setting::sptr& config,
                             const task_router::sptr& router) noexcept;

    };

}

#endif /* ROCKET_JOB_CONTEXT_H */
