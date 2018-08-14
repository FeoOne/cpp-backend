/**
 * @file job_context.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "job/job_loop.h"

#include "job/job_context.h"

namespace engine {

    using namespace framework;

    job_context::job_context(const event_queue::sptr& queue,
                             const event_recipient::sptr& recipient,
                             const config_setting::sptr& config) noexcept :
            execution_context(job_loop::make_unique(queue), queue, recipient, config)
    {
    }

    // virtual
    job_context::~job_context()
    {
    }

    // virtual
    void job_context::_before_run() noexcept
    {

    }

    // virtual
    void job_context::_after_run() noexcept
    {

    }

}
