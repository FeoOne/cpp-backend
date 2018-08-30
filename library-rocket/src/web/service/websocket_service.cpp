/**
 * @file websocket_service.cpp
 * @author Feo
 * @date 18/08/2018
 * @brief
 */

#include "web/service/webserver_service.h"
#include "web/task/ws_incoming_message_task.h"
#include "web/task/ws_outgoing_message_task.h"

#include "web/service/websocket_service.h"

namespace rocket {

    websocket_service::websocket_service(const groot::config_setting::sptr& config,
                                         const task_router::sptr& router,
                                         const work_service_delegate *service_provider) noexcept :
            crucial(config, router, service_provider)
    {
        RC_BIND_TASK_HANDLER(ws_outgoing_message_task, websocket_service, handle_ws_outgoing_message_task);
    }

    // virtual
    websocket_service::~websocket_service()
    {
    }

    void websocket_service::setup() noexcept
    {
        auto server = get_delegate()->get_service<webserver_service>()->get_server();
        if (server == nullptr) {
            logcrit("Failed to start http service w/o server.");
        }

        auto websocket_config = (*get_config())[consts::CONFIG_KEY_WEBSERVER_WEBSOCKET];
        auto path = (*websocket_config)[consts::CONFIG_KEY_PATH]->to_string_view(); // @todo Make array of pathes.

        soup_server_add_websocket_handler(server,
                                          path.data(),
                                          nullptr,
                                          nullptr,
                                          &websocket_service::handler_routine,
                                          this,
                                          nullptr);
    }

    void websocket_service::reset() noexcept
    {
        auto websocket_config = (*get_config())[consts::CONFIG_KEY_WEBSERVER_WEBSOCKET];
        auto path = (*websocket_config)[consts::CONFIG_KEY_PATH]->to_string_view();

        soup_server_remove_handler(get_delegate()->get_service<webserver_service>()->get_server(),
                                   path.data());
    }

    void websocket_service::handle_ws_outgoing_message_task(const task::sptr& t) noexcept
    {
        auto task = std::static_pointer_cast<ws_outgoing_message_task>(t);
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

        connection = GR_GOBJECT_REF(connection);

        g_signal_connect(connection, "message", G_CALLBACK(&websocket_service::message_routine), this);
        g_signal_connect(connection, "error", G_CALLBACK(&websocket_service::error_routine), this);
        g_signal_connect(connection, "closed", G_CALLBACK(&websocket_service::closed_routine), this);
    }

    void websocket_service::on_message(SoupWebsocketConnection *connection,
                                       SoupWebsocketDataType data_type,
                                       GBytes *data) noexcept
    {
        auto task = ws_incoming_message_task::make_shared(connection, data_type, data);
        get_router()->enqueue(task);
    }

    void websocket_service::on_error(SoupWebsocketConnection *connection, GError *error) noexcept
    {
        // @todo
    }

    void websocket_service::on_closed(SoupWebsocketConnection *connection) noexcept
    {
        g_signal_handlers_disconnect_by_data(connection, this);
        GR_GOBJECT_UNREF(connection);
    }

    // static
    void websocket_service::handler_routine(SoupServer *server,
                                            SoupWebsocketConnection *connection,
                                            const char *path,
                                            SoupClientContext *client,
                                            gpointer context) noexcept
    {
        static_cast<websocket_service *>(context)->on_handler(server, connection, path, client);
    }

    // static
    void websocket_service::message_routine(SoupWebsocketConnection *connection,
                                            SoupWebsocketDataType data_type,
                                            GBytes *data,
                                            gpointer context) noexcept
    {
        static_cast<websocket_service *>(context)->on_message(connection, data_type, data);
    }

    // static
    void websocket_service::error_routine(SoupWebsocketConnection *connection,
                                          GError *error,
                                          gpointer context) noexcept
    {
        static_cast<websocket_service *>(context)->on_error(connection, error);
    }

    // static
    void websocket_service::closed_routine(SoupWebsocketConnection *connection, gpointer context) noexcept
    {
        static_cast<websocket_service *>(context)->on_closed(connection);
    }

}
