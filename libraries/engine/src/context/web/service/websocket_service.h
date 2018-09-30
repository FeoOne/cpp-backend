/**
 * @file websocket_service.h
 * @author Feo
 * @date 18/08/2018
 * @brief
 */

#ifndef ENGINE_WEBSOCKET_SERVICE_H
#define ENGINE_WEBSOCKET_SERVICE_H

#include <libsoup/soup.h>

#include "work/work_service.h"

namespace engine {

    class websocket_service final : public stl::crucial<work_service, websocket_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(websocket_service)
        STL_DELETE_ALL_DEFAULT(websocket_service)

        explicit websocket_service(const stl::setting& config,
                                   task_router *router,
                                   const work_service_delegate *delegate) noexcept;
        virtual ~websocket_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_ws_outgoing_message_task(basic_task *base_task) noexcept;

        void on_handler(SoupServer *server,
                        SoupWebsocketConnection *connection,
                        const char *path,
                        SoupClientContext *client) noexcept;
        void on_message(SoupWebsocketConnection *connection,
                        SoupWebsocketDataType data_type,
                        GBytes *data) noexcept;
        void on_error(SoupWebsocketConnection *connection, GError *error) noexcept;
        void on_closed(SoupWebsocketConnection *connection) noexcept;

        static void handler_callback(SoupServer *server,
                                    SoupWebsocketConnection *connection,
                                    const char *path,
                                    SoupClientContext *client,
                                    gpointer context) noexcept;
        static void message_callback(SoupWebsocketConnection *connection,
                                    SoupWebsocketDataType data_type,
                                    GBytes *data,
                                    gpointer context) noexcept;
        static void error_callback(SoupWebsocketConnection *connection, GError *error, gpointer context) noexcept;
        static void closed_callback(SoupWebsocketConnection *connection, gpointer context) noexcept;

    };

}

#endif /* PROJECT_WEBSOCKET_SERVICE_H */
