/**
 * @file http_service.cpp
 * @author Feo
 * @date 18/08/2018
 * @brief
 */

#include "context/web/task/http_server_request_task.h"
#include "context/web/task/http_server_response_task.h"
#include "context/web/service/server_service.h"

#include "context/web/service/http_server_service.h"

namespace engine {

    http_server_service::http_server_service(const stl::setting& config,
                               task_router *router,
                               const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate)
    {
        EX_ASSIGN_TASK_HANDLER(http_server_response_task, http_server_service, handle_http_response_task);
    }

    // virtual
    http_server_service::~http_server_service()
    {
    }

    // virtual
    void http_server_service::setup() noexcept
    {
        setup_soup_server();
    }

    // virtual
    void http_server_service::reset() noexcept
    {
        reset_soup_server();
    }

    void http_server_service::setup_soup_server() noexcept
    {
        auto server { delegate()->service<server_service>()->soup_server() };
        if (server == nullptr) {
            logcrit("Failed to start http service w/o server.");
        }

        soup_server_add_handler(server,
                                consts::webserver::default_http_route,
                                &http_server_service::handler_callback,
                                this,
                                nullptr);
    }

    void http_server_service::reset_soup_server() noexcept
    {
        soup_server_remove_handler(delegate()->service<server_service>()->soup_server(),
                                   consts::webserver::default_http_route);
    }

    void http_server_service::handle_http_response_task(basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<engine::http_server_response_task *>(base_task) };
        auto response { task->get_response() };
        auto request { response->get_request() };

        soup_server_unpause_message(delegate()->service<server_service>()->soup_server(),
                                    request->get_message());
    }

    void http_server_service::handler(SoupServer *server,
                               SoupMessage *message,
                               const char *path,
                               GHashTable *query,
                               SoupClientContext *client) noexcept
    {
        logdebug("HTTP handler fired. Host: %s, user: %s.",
                 soup_client_context_get_host(client),
                 soup_client_context_get_auth_user(client));
        logassert(delegate()->service<server_service>()->soup_server() == server,
                  "Can't process http request from different server.");

//        std::string_view p { path };
//        auto request { http_server_request::make_shared(message, p, query, client) };
//        auto task { new (std::nothrow) http_server_request_task(request) };
//        router()->enqueue(task);

        soup_server_pause_message(delegate()->service<server_service>()->soup_server(), message);
    }

    // static
    void http_server_service::handler_callback(SoupServer *server,
                                       SoupMessage *message,
                                       const char *path,
                                       GHashTable *query,
                                       SoupClientContext *client,
                                       gpointer context) noexcept
    {
        auto self { static_cast<http_server_service *>(context) };
        if (self != nullptr) {
            self->handler(server, message, path, query, client);
        } else {
            logwarn("Can't process empty context for path '%s'.", path);
        }
    }

}
