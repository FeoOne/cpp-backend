/**
 * @file n_context.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef BACKEND_BACKEND_CONTEXT_H
#define BACKEND_BACKEND_CONTEXT_H

#include <engine.h>

namespace backend {

    class job_context : public engine::job_context {
    public:
        STL_DECLARE_SMARTPOINTERS(job_context)
        STL_DELETE_ALL_DEFAULT(job_context)

        explicit job_context(const stl::setting& config, engine::task_router *router) noexcept;
        virtual ~job_context() = default;

    private:

    };

}

#endif /* BACKEND_BACKEND_CONTEXT_H */
