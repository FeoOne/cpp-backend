/**
 * @file io_work_context.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include "io/io_loop.h"
#include "io/service/tcp_service.h"
#include "io/service/udp_service.h"
#include "io/service/message_filter_service.h"
#include "io/task/outgoing_message_task.h"

#include "io/io_context.h"

using namespace framework;

namespace engine {

    io_context::io_context(const config_setting::sptr& config,
                           const task_router::sptr& router) noexcept :
            crucial(config, router, io_loop::make_shared(router->get_queue<io_context>(), this))
    {
        add_service(tcp_service::make_shared(get_config(), get_router(), this));
        add_service(udp_service::make_shared(get_config(), get_router(), this));
        add_service(message_filter_service::make_shared(get_config(), get_router(), this));

        register_task_handler(outgoing_message_task::key(), message_filter_service::key());
    }

    // virtual
    io_context::~io_context()
    {
        remove_service<message_filter_service>();
        remove_service<udp_service>();
        remove_service<tcp_service>();
    }

    // virtual
    void io_context::setup() noexcept
    {
        get_service<tcp_service>()->setup();
        get_service<udp_service>()->setup();
        get_service<message_filter_service>()->setup();
    }

    // virtual
    void io_context::reset() noexcept
    {
        get_service<message_filter_service>()->reset();
        get_service<udp_service>()->reset();
        get_service<tcp_service>()->reset();
    }

}
