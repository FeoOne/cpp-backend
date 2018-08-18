/**
 * @file job_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "job/job_loop.h"

namespace engine {

    job_loop::job_loop(const task_queue::sptr& queue) noexcept :
            work_loop(queue)
    {
    }

    // virtual
    job_loop::~job_loop()
    {
    }

    // virtual
    void job_loop::start() noexcept
    {

    }

    // virtual
    void job_loop::stop() noexcept
    {

    }

}
