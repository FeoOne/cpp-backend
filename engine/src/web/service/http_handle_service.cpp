/**
 * @file http_handle_service.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "main/engine_const.h"
#include "web/http/http_request.h"
#include "web/event/http_request_event.h"

#include "web/service/http_handle_service.h"

namespace engine {

    using namespace framework;

    http_handle_service::http_handle_service(const event_recipient::sptr& recipient, SoupServer *server) noexcept :
            web_server_service(recipient, server)
    {
        soup_server_add_handler(get_server(),
                                engine_const::WEB_SERVER_DEFAULT_HTTP_ROUTE.data(),
                                &http_handle_service::handler,
                                this,
                                nullptr);
    }

    // virtual
    http_handle_service::~http_handle_service()
    {
        soup_server_remove_handler(get_server(), engine_const::WEB_SERVER_DEFAULT_HTTP_ROUTE.data());
    }

    void http_handle_service::handler(SoupServer *server,
                                      SoupMessage *message,
                                      const char *path,
                                      GHashTable *query,
                                      SoupClientContext *client) noexcept
    {
        // @todo Compare server pointers for extra error check.
        logdebug("HTTP handler fired. Host: %s, user: %s.",
                 soup_client_context_get_host(client),
                 soup_client_context_get_auth_user(client));

        std::string_view p { path };
        auto request { http_request::make_shared(message, p, query, client) };
        recipient()->enqueue(http_request_event::make_shared(request));

        soup_server_pause_message(get_server(), message);
    }

    // static
    void http_handle_service::handler(SoupServer *server,
                                      SoupMessage *message,
                                      const char *path,
                                      GHashTable *query,
                                      SoupClientContext *client,
                                      gpointer context) noexcept
    {
        auto self = static_cast<http_handle_service *>(context);
        self->handler(server, message, path, query, client);
    }

}
