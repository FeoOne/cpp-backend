//
// Created by Feo on 07/12/2018.
//

#include "context/web/service/http_client_service.h"

namespace engine {

    http_client_service::http_client_service(const stl::setting& config,
                                             task_router *router,
                                             const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _session { nullptr }
    {

    }

    // virtual
    http_client_service::~http_client_service()
    {
    }

    // virtual
    void http_client_service::setup() noexcept
    {
        setup_session();
    }

    // virtual
    void http_client_service::reset() noexcept
    {
        reset_session();
    }

    void http_client_service::setup_session() noexcept
    {
        _session = soup_session_new_with_options(SOUP_SESSION_ADD_FEATURE_BY_TYPE, SOUP_TYPE_CONTENT_SNIFFER, NULL);

#ifndef NDEBUG
        auto logger { soup_logger_new(SoupLoggerLogLevel::SOUP_LOGGER_LOG_HEADERS, -1) };
        soup_session_add_feature(_session, SOUP_SESSION_FEATURE(logger));
        STL_GOBJECT_RELEASE(logger);
#endif
    }

    void http_client_service::reset_session() noexcept
    {
        soup_session_abort(_session);
        STL_GOBJECT_RELEASE(_session);
        _session = nullptr;
    }

}
