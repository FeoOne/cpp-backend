/**
 * @file job_context.cpp
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#include "job/job_context.h"

namespace strange {

    job_context::job_context(const groot::setting& config, rocket::task_router *router) noexcept :
            rocket::job_context(config, router)
    {

    }

}
