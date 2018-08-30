/**
 * @file message_distribution_service.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "io/task/outgoing_message_task.h"

#include "io/service/message_filter_service.h"

namespace rocket {

    message_filter_service::message_filter_service(const groot::config_setting::sptr& config,
                                                   const task_router::sptr& router,
                                                   const work_service_delegate *service_provider) noexcept :
            crucial(config, router, service_provider)
    {
        RC_BIND_TASK_HANDLER(outgoing_message_task, message_filter_service, handle_outgoing_packet_task);
    }

    // virtual
    message_filter_service::~message_filter_service()
    {
    }

    void message_filter_service::setup() noexcept
    {

    }

    void message_filter_service::reset() noexcept
    {

    }

    void message_filter_service::handle_outgoing_packet_task(const rocket::task::sptr& t) noexcept
    {

    }

}
