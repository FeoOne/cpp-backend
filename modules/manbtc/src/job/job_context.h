//
// Created by Feo on 15/10/2018.
//

#ifndef MANBTC_JOB_CONTEXT_H
#define MANBTC_JOB_CONTEXT_H

#include <engine.h>

namespace manbtc {

    class job_context : public engine::job_context {
    public:
        STL_DECLARE_SMARTPOINTERS(job_context)
        STL_DELETE_ALL_DEFAULT(job_context)

        explicit job_context(const stl::setting& config, engine::task_router *router) noexcept;
        virtual ~job_context() = default;

    private:
    };

}

#endif /* MANBTC_JOB_CONTEXT_H */
