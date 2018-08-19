/**
 * @file job_context.cpp
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#include "job/service/http_service.h"

#include "job/backend_context.h"

namespace backend {

    backend_context::backend_context(const framework::config_setting::sptr& config,
                                     const engine::task_router::sptr& router) noexcept :
            job_context(config, router)
    {
        add_service(http_service::make_shared(get_config(), get_router(), this));

        register_task_handler(engine::http_request_task::key(), http_service::key());
    }

    // virtual
    backend_context::~backend_context()
    {
    }

    // virtual
    void backend_context::setup() noexcept
    {

    }

    // virtual
    void backend_context::reset() noexcept
    {

    }

}
