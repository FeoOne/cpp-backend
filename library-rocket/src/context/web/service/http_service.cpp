/**
 * @file http_service.cpp
 * @author Feo
 * @date 18/08/2018
 * @brief
 */

#include "context/web/task/http_request_task.h"
#include "context/web/task/http_response_task.h"
#include "context/web/service/webserver_service.h"

#include "context/web/service/http_service.h"

namespace rocket {

    http_service::http_service(const groot::setting& config,
                               task_router *router,
                               const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate)
    {
        RC_ASSIGN_TASK_HANDLER(http_response_task, http_service, handle_http_response_task);
    }

    // virtual
    http_service::~http_service()
    {
    }

    // virtual
    void http_service::setup() noexcept
    {
        auto server { delegate()->service<webserver_service>()->get_server() };
        if (server == nullptr) {
            logcrit("Failed to start http service w/o server.");
        }

        soup_server_add_handler(server,
                                consts::WEB_DEFAULT_HTTP_ROUTE.data(),
                                &http_service::handler_callback,
                                this,
                                nullptr);
    }

    // virtual
    void http_service::reset() noexcept
    {
        soup_server_remove_handler(delegate()->service<webserver_service>()->get_server(),
                                   consts::WEB_DEFAULT_HTTP_ROUTE.data());
    }

    void http_service::handle_http_response_task(basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<rocket::http_response_task *>(base_task) };
        auto response { task->get_response() };
        auto request { response->get_request() };

        soup_server_unpause_message(delegate()->service<webserver_service>()->get_server(),
                                    request->get_message());

        basic_task::destroy(task);
    }

    void http_service::handler(SoupServer *server,
                               SoupMessage *message,
                               const char *path,
                               GHashTable *query,
                               SoupClientContext *client) noexcept
    {
        logdebug("HTTP handler fired. Host: %s, user: %s.",
                 soup_client_context_get_host(client),
                 soup_client_context_get_auth_user(client));
        logassert(delegate()->service<webserver_service>()->get_server() == server,
                  "Can't process http request from different server.");

        std::string_view p { path };
        auto request { http_request::make_shared(message, p, query, client) };
        auto task { basic_task::create<http_request_task>(request) };
        router()->enqueue(task);

        soup_server_pause_message(delegate()->service<webserver_service>()->get_server(), message);
    }

    // static
    void http_service::handler_callback(SoupServer *server,
                                       SoupMessage *message,
                                       const char *path,
                                       GHashTable *query,
                                       SoupClientContext *client,
                                       gpointer context) noexcept
    {
        auto self { static_cast<http_service *>(context) };
        if (self != nullptr) {
            self->handler(server, message, path, query, client);
        } else {
            logwarn("Can't process empty context for path '%s'.", path);
        }
    }

}
