/**
 * @file websocket_handle_service.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "web/service/websocket_handle_service.h"

namespace engine {

    websocket_handle_service::websocket_handle_service(const event_recipient::sptr& recipient, SoupServer *server) noexcept :
            web_server_service(recipient, server)
    {
//        soup_server_add_websocket_handler(_server,
//                                          "/websocket",
//                                          nullptr,
//                                          nullptr,
//                                          &websocket_handle_service::_handler,
//                                          this,
//                                          nullptr);
    }

    // virtual
    websocket_handle_service::~websocket_handle_service()
    {
//        soup_server_remove_handler(_server, "/websocket");
    }

    void websocket_handle_service::_handler(SoupServer *server,
                                            SoupWebsocketConnection *connection,
                                            const char *path,
                                            SoupClientContext *client) noexcept
    {
        // @todo Compare server pointers for extra error check.
        logdebug("WebSocket handler fired. Host: %s, user: %s.",
                 soup_client_context_get_host(client),
                 soup_client_context_get_auth_user(client));


    }

    //static
    void websocket_handle_service::_handler(SoupServer *server,
                                            SoupWebsocketConnection *connection,
                                            const char *path,
                                            SoupClientContext *client,
                                            gpointer context) noexcept
    {
        auto self = static_cast<websocket_handle_service *>(context);
        self->_handler(server, connection, path, client);
    }

}
