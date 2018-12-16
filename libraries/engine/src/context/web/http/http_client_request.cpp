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
    }

    void http_client_request::set_body(const std::string& body) noexcept
    {
        soup_message_headers_append(_message->request_headers,
                                    "Accept",
                                    engine::http_client_request::content_type::json);

        soup_message_set_request(_message,
                                 engine::http_client_request::content_type::json,
                                 SoupMemoryUse::SOUP_MEMORY_COPY,
                                 body.data(),
                                 body.size());
    }

    void http_client_request::set_credentials(const char *credentials) noexcept
    {
        std::string data { "Basic " + stl::crypto::base64_encode(credentials) };
        soup_message_headers_append(_message->request_headers,
                                    "Authorization",
                                    data.data());
    }

}
