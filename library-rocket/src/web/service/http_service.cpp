/**
 * @file http_service.cpp
 * @author Feo
 * @date 18/08/2018
 * @brief
 */

#include "web/task/http_request_task.h"
#include "web/task/http_response_task.h"
#include "web/service/webserver_service.h"

#include "web/service/http_service.h"

namespace rocket {

    http_service::http_service(const groot::config_setting::sptr& config,
                               const task_router::sptr& router,
                               const work_context_delegate *service_provider) noexcept :
            crucial(config, router, service_provider)
    {
        EG_BIND_TASK_HANDLER(http_response_task, http_service, handle_http_response_task);
    }

    // virtual
    http_service::~http_service()
    {
    }

    // virtual
    void http_service::setup() noexcept
    {
        soup_server_add_handler(get_context_delegate()->get_service<webserver_service>()->get_server(),
                                consts::WEB_SERVER_DEFAULT_HTTP_ROUTE.data(),
                                &http_service::handler_routine,
                                this,
                                nullptr);
    }

    // virtual
    void http_service::reset() noexcept
    {
        soup_server_remove_handler(get_context_delegate()->get_service<webserver_service>()->get_server(),
                                   consts::WEB_SERVER_DEFAULT_HTTP_ROUTE.data());
    }

    void http_service::handle_http_response_task(const rocket::task::sptr& t) noexcept
    {
        auto task = std::static_pointer_cast<rocket::http_response_task>(t);
        auto response = task->get_response();
        auto request = response->get_request();

        soup_server_unpause_message(get_context_delegate()->get_service<webserver_service>()->get_server(),
                                    request->get_message());
    }

    void http_service::handler(SoupServer *server,
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
        get_router()->enqueue(http_request_task::make_shared(request));

        soup_server_pause_message(get_context_delegate()->get_service<webserver_service>()->get_server(), message);
    }

    // static
    void http_service::handler_routine(SoupServer *server,
                                       SoupMessage *message,
                                       const char *path,
                                       GHashTable *query,
                                       SoupClientContext *client,
                                       gpointer context) noexcept
    {
        static_cast<http_service *>(context)->handler(server, message, path, query, client);
    }

}
