/**
 * @file websocket_handle_service.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_WEBSOCKET_HANDLE_SERVICE_H
#define ENGINE_WEBSOCKET_HANDLE_SERVICE_H

#include <libsoup/soup.h>

#include "web/service/web_server_service.h"

namespace engine {

    class websocket_handle_service final : public web_server_service<websocket_handle_service> {
    public:
        FW_DECLARE_SMARTPOINTERS(websocket_handle_service)
        FW_DELETE_ALL_DEFAULT(websocket_handle_service)

        explicit websocket_handle_service(const event_router::sptr& router, SoupServer *server) noexcept;
        virtual ~websocket_handle_service();

    private:
        void _handler(SoupServer *server,
                      SoupWebsocketConnection *connection,
                      const char *path,
                      SoupClientContext *client) noexcept;

        static void _handler(SoupServer *server,
                             SoupWebsocketConnection *connection,
                             const char *path,
                             SoupClientContext *client,
                             gpointer context) noexcept;

    };

}

#endif /* ENGINE_WEBSOCKET_HANDLE_SERVICE_H */
