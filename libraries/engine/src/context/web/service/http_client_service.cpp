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
            _session { nullptr }
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
    }

    void http_client_service::on_handler(GObject *object, GAsyncResult *result) noexcept
    {

    }

    // static
    void http_client_service::handler_callback(GObject *object, GAsyncResult *result, gpointer user_data) noexcept
    {

    }

}
