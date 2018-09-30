/**
 * @file job_context.h
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#ifndef DATABASE_JOB_CONTEXT_H
#define DATABASE_JOB_CONTEXT_H

#include <engine.h>

namespace database {

    class job_context : public engine::job_context {
    public:
        STL_DECLARE_SMARTPOINTERS(job_context)
        STL_DELETE_ALL_DEFAULT(job_context)

        explicit job_context(const stl::setting& config, engine::task_router *router) noexcept;
        virtual ~job_context() = default;

    private:


    };

}

#endif /* DATABASE_JOB_CONTEXT_H */
