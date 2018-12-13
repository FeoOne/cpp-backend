//
// Created by Feo on 07/12/2018.
//

#include "http_client_request.h"

namespace engine {

    http_client_request::http_client_request(const char *method, const char *uri) noexcept :
            _message { soup_message_new(method, uri) }
    {
    }

    http_client_request::http_client_request(const char *method, SoupURI *uri) noexcept :
            _message { soup_message_new_from_uri(method, uri) }
    {
    }

    http_client_request::~http_client_request()
    {
        if (_message != nullptr) {
            STL_GOBJECT_RELEASE(_message);
        }
    }

    void http_client_request::set_body(const char *cont_type, const std::string& data) noexcept
    {
        soup_message_set_request(_message, cont_type, SOUP_MEMORY_COPY, data.data(), data.size());
    }

}
