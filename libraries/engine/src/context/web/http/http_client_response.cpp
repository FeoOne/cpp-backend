//
// Created by Feo on 12/12/2018.
//

#include "context/web/http/http_client_response.h"

namespace engine {

    http_client_response::http_client_response(SoupMessage *message) noexcept :
            _message { message }
    {
        STL_GOBJECT_RETAIN(_message);
    }

    http_client_response::~http_client_response()
    {
        STL_GOBJECT_RELEASE(_message);
    }

    u32 http_client_response::status_code() const noexcept
    {
        return _message->status_code;
    }

    SoupMessageBody *http_client_response::body() noexcept
    {
        return _message->response_body;
    }

}
