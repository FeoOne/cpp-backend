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
        STL_GOBJECT_RELEASE(_message);
    }

}
