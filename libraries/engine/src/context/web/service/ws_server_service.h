/**
 * @file ws_service.h
 * @author Feo
 * @date 18/08/2018
 * @brief
 */

#ifndef ENGINE_WS_SERVICE_H
#define ENGINE_WS_SERVICE_H

#include <libsoup/soup.h>

#include "work/service/work_service.h"

namespace engine {

    class ws_server_service final : public stl::crucial<work_service, ws_server_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(ws_server_service)
        STL_DELETE_ALL_DEFAULT(ws_server_service)

        explicit ws_server_service(const stl::setting& config,
                                   task_router *router,
                                   const work_service_delegate *delegate) noexcept;
        virtual ~ws_server_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_ws_response_task(basic_task *base_task) noexcept;
        void handle_ws_disconnect_task(basic_task *base_task) noexcept;

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

#endif /* ENGINE_WS_SERVICE_H */
