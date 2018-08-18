/**
 * @file webserver_context.cpp
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#include "web/webserver_loop.h"
#include "web/service/webserver_service.h"
#include "web/service/http_service.h"
#include "web/service/websocket_service.h"

#include "web/webserver_context.h"

using namespace framework;

namespace engine {

    webserver_context::webserver_context(const config_setting::sptr& config,
                                         const task_router::sptr& router) noexcept :
            crucial(config, router, webserver_loop::make_shared(router->get_queue<webserver_context>()))
    {
        add_service(webserver_service::make_shared(get_config(), get_router(), this));
        add_service(http_service::make_shared(get_config(), get_router(), this));
        add_service(websocket_service::make_shared(get_config(), get_router(), this));
    }

    // virtual
    webserver_context::~webserver_context()
    {
        remove_service<websocket_service>();
        remove_service<http_service>();
        remove_service<webserver_service>();
    }

    // virtual
    void webserver_context::setup() noexcept
    {
        get_service<webserver_service>()->setup();
        get_service<http_service>()->setup();
        get_service<websocket_service>()->setup();
    }

    // virtual
    void webserver_context::reset() noexcept
    {
        get_service<websocket_service>()->reset();
        get_service<http_service>()->reset();
        get_service<webserver_service>()->reset();
    }

}
