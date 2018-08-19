/**
 * @file http_response.cpp
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#include "web/http/http_response.h"

namespace engine {

    http_response::http_response(const http_request::sptr& request, SoupStatus status) noexcept :
            _request { request }
    {
        soup_message_set_status(request->get_message(), status);
    }

}
