/**
 * @file job_context.h
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#ifndef STRANGE_JOB_CONTEXT_H
#define STRANGE_JOB_CONTEXT_H

#include <rocket.h>

namespace strange {

    class job_context : public rocket::job_context {
    public:
        GR_DECLARE_SMARTPOINTERS(job_context)
        GR_DELETE_ALL_DEFAULT(job_context)

        explicit job_context(const groot::config_setting::sptr& config,
                             const rocket::task_router::sptr& router) noexcept;
        virtual ~job_context();

    private:
        void setup() noexcept final;
        void reset() noexcept final;

    };

}

#endif /* STRANGE_JOB_CONTEXT_H */
