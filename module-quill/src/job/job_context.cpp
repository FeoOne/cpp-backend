/**
 * @file job_context.cpp
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#include "job/service/http_service.h"

#include "job/job_context.h"

namespace quill {

    job_context::job_context(const groot::config_setting::sptr& config,
                             const rocket::task_router::sptr& router) noexcept :
            rocket::job_context(config, router)
    {
        add_service(http_service::make_shared(get_config(), get_router(), this));

        register_task_handler(rocket::http_request_task::key(), http_service::key());
    }

    // virtual
    job_context::~job_context()
    {
        remove_service<http_service>();
    }

    // virtual
    void job_context::setup() noexcept
    {
        get_service<http_service>()->setup();
    }

    // virtual
    void job_context::reset() noexcept
    {
        get_service<http_service>()->reset();
    }

}
