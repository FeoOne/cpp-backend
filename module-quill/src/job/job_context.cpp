/**
 * @file job_context.cpp
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#include "job/service/websocket_service.h"

#include "job/job_context.h"

namespace quill {

    job_context::job_context(const groot::config_setting::sptr& config,
                             const rocket::task_router::sptr& router) noexcept :
            rocket::job_context(config, router)
    {
        add_service(websocket_service::make_shared(get_config(), get_router(), this));

        register_task_handler(rocket::ws_incoming_message_task::key(), websocket_service::key());
    }

    // virtual
    job_context::~job_context()
    {
        remove_service<websocket_service>();
    }

    // virtual
    void job_context::setup() noexcept
    {
        get_service<websocket_service>()->setup();
    }

    // virtual
    void job_context::reset() noexcept
    {
        get_service<websocket_service>()->reset();
    }

}
