/**
 * @file n_context.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef QUILL_BACKEND_CONTEXT_H
#define QUILL_BACKEND_CONTEXT_H

#include <rocket.h>

namespace quill {

    class job_context : public rocket::job_context {
    public:
        GR_DECLARE_SMARTPOINTERS(job_context)
        GR_DELETE_ALL_DEFAULT(job_context)

        explicit job_context(const groot::setting& config, rocket::task_router *router) noexcept;
        virtual ~job_context() = default;

    private:

    };

}

#endif /* QUILL_BACKEND_CONTEXT_H */
