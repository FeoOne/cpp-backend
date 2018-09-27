/**
 * @file job_context.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "context/job/job_loop.h"

#include "context/job/job_context.h"

namespace rocket {

    job_context::job_context(const groot::setting& config, rocket::task_router *router) noexcept :
            crucial(config, router, job_loop::make_unique(router->get_queue<job_context>(), this))
    {
    }

}
