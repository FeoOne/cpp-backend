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

    class job_context : public stl::crucial<work_context, job_context> {
    public:
        STL_DECLARE_SMARTPOINTERS(job_context)
        STL_DELETE_ALL_DEFAULT(job_context)

        virtual ~job_context() = default;

    protected:
        explicit job_context(const stl::setting& config, task_router *router) noexcept;

    };

}

#endif /* ENGINE_JOB_CONTEXT_H */
