/**
 * @file http_response.cpp
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#include "context/web/http/http_server_response.h"

namespace engine {

    http_server_response::http_server_response(const http_server_request::sptr& request) noexcept :
            _request { request }
    {
    }

    void http_server_response::set_status(SoupStatus status) noexcept
    {
        soup_message_set_status(_request->get_message(), status);
    }

    void http_server_response::set_view(const web_view::sptr& view) noexcept
    {
        const auto& content = view->compile_and_get_body();
        soup_message_set_response(_request->get_message(),
                                  "text/html",
                                  SOUP_MEMORY_COPY,
                                  content.c_str(),
                                  content.length());
    }

}
