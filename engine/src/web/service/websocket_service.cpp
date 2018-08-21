/**
 * @file websocket_service.cpp
 * @author Feo
 * @date 18/08/2018
 * @brief
 */

#include "web/service/webserver_service.h"

#include "web/service/websocket_service.h"

namespace engine {

    websocket_service::websocket_service(const framework::config_setting::sptr& config,
                                         const task_router::sptr& router,
                                         const work_context_delegate *service_provider) noexcept :
            crucial(config, router, service_provider)
    {
    }

    // virtual
    websocket_service::~websocket_service()
    {
    }

    void websocket_service::setup() noexcept
    {
//        soup_server_add_websocket_handler(_server,
//                                          "/websocket",
//                                          nullptr,
//                                          nullptr,
//                                          &websocket_handle_service::_handler,
//                                          this,
//                                          nullptr);
    }

    void websocket_service::reset() noexcept
    {
//        soup_server_remove_handler(_server, "/websocket");
    }

    void websocket_service::handler(SoupServer *server,
                                    SoupWebsocketConnection *connection,
                                    const char *path,
                                    SoupClientContext *client) noexcept
    {
        // @todo Compare server pointers for extra error check.
        logdebug("WebSocket handler fired. Host: %s, user: %s.",
                 soup_client_context_get_host(client),
                 soup_client_context_get_auth_user(client));
    }

    // static
    void websocket_service::handler_routine(SoupServer *server,
                                            SoupWebsocketConnection *connection,
                                            const char *path,
                                            SoupClientContext *client,
                                            gpointer context) noexcept
    {
        static_cast<websocket_service *>(context)->handler(server, connection, path, client);
    }

}
