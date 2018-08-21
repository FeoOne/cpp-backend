/**
 * @file job_context.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "job/job_loop.h"

#include "job/job_context.h"

namespace rocket {

    job_context::job_context(const groot::config_setting::sptr& config,
                             const task_router::sptr& router) noexcept :
            crucial(config, router, job_loop::make_shared(router->get_queue<job_context>(), this))
    {
    }

}
