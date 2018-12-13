//
// Created by Feo on 07/12/2018.
//

#include "context/web/task/http_client_request_task.h"

#include "context/web/service/http_client_service.h"

namespace engine {

    http_client_service::http_client_service(const stl::setting& config,
                                             task_router *router,
                                             const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _session { nullptr },
            _requests {},
            _request_pool { stl::fixed_memory_pool::make_unique(sizeof(request_context), stl::memory::page_size()) }
    {
        EX_ASSIGN_TASK_HANDLER(http_client_request_task, http_client_service, handle_http_client_request_task);
    }

    // virtual
    http_client_service::~http_client_service()
    {
    }

    // virtual
    void http_client_service::setup() noexcept
    {
        setup_soup_session();
    }

    // virtual
    void http_client_service::reset() noexcept
    {
        reset_soup_session();
    }

    void http_client_service::setup_soup_session() noexcept
    {
        _session = soup_session_new_with_options(SOUP_SESSION_ADD_FEATURE_BY_TYPE, SOUP_TYPE_CONTENT_SNIFFER, NULL);

        auto logger { soup_logger_new(SoupLoggerLogLevel::SOUP_LOGGER_LOG_HEADERS, -1) };
        soup_session_add_feature(_session, SOUP_SESSION_FEATURE(logger));
        STL_GOBJECT_RELEASE(logger);

        soup_session_add_feature_by_type(_session, SOUP_TYPE_AUTH_BASIC);
    }

    void http_client_service::reset_soup_session() noexcept
    {
        if (_session != nullptr) {
            soup_session_abort(_session);
            STL_GOBJECT_RELEASE(_session);
            _session = nullptr;
        }
    }

    void http_client_service::handle_http_client_request_task(basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<http_client_request_task *>(base_task) };
        auto request { task->request() };

        auto context { new (_request_pool->alloc()) request_context };
        context->service = this;
        context->callback = task->grab_callback();

        soup_session_queue_message(_session, request->message(), &http_client_service::handler_callback, context);

        delete request;
    }

    void http_client_service::on_handler(SoupSession *session,
                                         SoupMessage *message,
                                         http_client_request_task::response_callback&& callback) noexcept
    {

    }

    // static
    void http_client_service::handler_callback(SoupSession *session, SoupMessage *message, gpointer user_data) noexcept
    {
        if (user_data != nullptr) {
            auto context = reinterpret_cast<request_context *>(user_data);
            context->service->on_handler(session, message, std::move(context->callback));
        }
    }

}
