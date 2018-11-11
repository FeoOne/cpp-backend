//
// Created by Feo on 15/10/2018.
//

#include "job/job_context.h"

namespace manbtc {

    job_context::job_context(const stl::setting& config, engine::task_router *router) noexcept :
            engine::job_context(config, router)
    {
    }

}
