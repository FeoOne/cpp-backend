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
#include "web/task/http_response_task.h"
#include "web/task/ws_outgoing_message_task.h"

#include "web/webserver_context.h"

namespace rocket {

    webserver_context::webserver_context(const groot::config_setting::sptr& config,
                                         const task_router::sptr& router) noexcept :
            crucial(config, router, webserver_loop::make_shared(router->get_queue<webserver_context>(), this)),
            _websocket_enabled { (*config)[consts::CONFIG_KEY_WEBSERVER_WEBSOCKET] }
    {
        add_service(webserver_service::make_shared(get_config(), get_router(), this));
        add_service(http_service::make_shared(get_config(), get_router(), this));
        if (_websocket_enabled) {
            lognotice("Websocket enabled.");
            add_service(websocket_service::make_shared(get_config(), get_router(), this));
        }

        register_task_handler(http_response_task::key(), http_service::key());
        register_task_handler(ws_outgoing_message_task::key(), websocket_service::key());
    }

    // virtual
    webserver_context::~webserver_context()
    {
        if (_websocket_enabled) {
            remove_service<websocket_service>();
        }
        remove_service<http_service>();
        remove_service<webserver_service>();
    }

    // virtual
    void webserver_context::setup() noexcept
    {
        get_service<webserver_service>()->setup();
        get_service<http_service>()->setup();
        if (_websocket_enabled) {
            get_service<websocket_service>()->setup();
        }
    }

    // virtual
    void webserver_context::reset() noexcept
    {
        if (_websocket_enabled) {
            get_service<websocket_service>()->reset();
        }
        get_service<http_service>()->reset();
        get_service<webserver_service>()->reset();
    }

}
