/**
 * @file job_context.cpp
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#include "job/job_context.h"

namespace strange {

    job_context::job_context(const groot::setting& config,
                             const rocket::task_router::sptr& router) noexcept :
            rocket::job_context(config, router)
    {

    }

    // virtual
    job_context::~job_context()
    {

    }

    // virtual
    void job_context::setup() noexcept
    {

    }

    // virtual
    void job_context::reset() noexcept
    {

    }

}
