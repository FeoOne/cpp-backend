/**
 * @file websocket_service.cpp
 * @author Feo
 * @date 18/08/2018
 * @brief
 */

#include "context/web/service/webserver_service.h"
#include "context/web/task/ws_request_task.h"
#include "context/web/task/ws_response_task.h"
#include "context/web/task/ws_disconnect_task.h"

#include "context/web/service/websocket_service.h"

namespace engine {

    websocket_service::websocket_service(const stl::setting& config,
                                         task_router *router,
                                         const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate)
    {
        EX_ASSIGN_TASK_HANDLER(ws_response_task, websocket_service, handle_ws_response_task);
        EX_ASSIGN_TASK_HANDLER(ws_disconnect_task, websocket_service, handle_ws_disconnect_task);
    }

    // virtual
    websocket_service::~websocket_service()
    {
    }

    void websocket_service::setup() noexcept
    {
        auto server { delegate()->service<webserver_service>()->get_server() };
        if (server == nullptr) {
            logcrit("Failed to start websocket service w/o server.");
        }

        auto websocket_config { config()[consts::config::key::WEBSOCKET] };
        auto path { websocket_config[consts::config::key::PATH].to_string() }; // @todo Make array of pathes.

        soup_server_add_websocket_handler(server,
                                          path.data(),
                                          nullptr,
                                          nullptr,
                                          &websocket_service::handler_callback,
                                          this,
                                          nullptr);
    }

    void websocket_service::reset() noexcept
    {
        auto websocket_config { config()[consts::config::key::WEBSOCKET] };
        auto path { websocket_config[consts::config::key::PATH].to_string() };

        soup_server_remove_handler(delegate()->service<webserver_service>()->get_server(),
                                   path.data());
    }

    void websocket_service::handle_ws_response_task(basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<ws_response_task *>(base_task) };

        // todo: implement
    }

    void websocket_service::handle_ws_disconnect_task(basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<ws_disconnect_task *>(base_task) };
        soup_websocket_connection_close(task->connection(), task->code(), nullptr);
    }

    void websocket_service::on_handler(SoupServer *server,
                                       SoupWebsocketConnection *connection,
                                       const char *path,
                                       SoupClientContext *client) noexcept
    {
        // @todo Compare server pointers for extra error check.
        logdebug("WebSocket handler fired. Host: %s, user: %s.",
                 soup_client_context_get_host(client),
                 soup_client_context_get_auth_user(client));

        STL_GOBJECT_RETAIN(connection);

        g_signal_connect(connection, "message", G_CALLBACK(&websocket_service::message_callback), this);
        g_signal_connect(connection, "error", G_CALLBACK(&websocket_service::error_callback), this);
        g_signal_connect(connection, "closed", G_CALLBACK(&websocket_service::closed_callback), this);
    }

    void websocket_service::on_message(SoupWebsocketConnection *connection,
                                       SoupWebsocketDataType data_type,
                                       GBytes *data) noexcept
    {
        auto task { basic_task::create<ws_request_task>(connection, data_type, data) };
        router()->enqueue(task);
    }

    void websocket_service::on_error(SoupWebsocketConnection *connection, GError *error) noexcept
    {
        // @todo
    }

    void websocket_service::on_closed(SoupWebsocketConnection *connection) noexcept
    {
        g_signal_handlers_disconnect_by_data(connection, this);
        STL_GOBJECT_RELEASE(connection);
    }

    // static
    void websocket_service::handler_callback(SoupServer *server,
                                            SoupWebsocketConnection *connection,
                                            const char *path,
                                            SoupClientContext *client,
                                            gpointer context) noexcept
    {
        static_cast<websocket_service *>(context)->on_handler(server, connection, path, client);
    }

    // static
    void websocket_service::message_callback(SoupWebsocketConnection *connection,
                                            SoupWebsocketDataType data_type,
                                            GBytes *data,
                                            gpointer context) noexcept
    {
        static_cast<websocket_service *>(context)->on_message(connection, data_type, data);
    }

    // static
    void websocket_service::error_callback(SoupWebsocketConnection *connection,
                                          GError *error,
                                          gpointer context) noexcept
    {
        static_cast<websocket_service *>(context)->on_error(connection, error);
    }

    // static
    void websocket_service::closed_callback(SoupWebsocketConnection *connection, gpointer context) noexcept
    {
        static_cast<websocket_service *>(context)->on_closed(connection);
    }

}
