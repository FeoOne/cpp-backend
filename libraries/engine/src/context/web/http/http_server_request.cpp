/**
 * @file http_request.cpp
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#include "context/web/http/http_server_request.h"

namespace engine {

    http_server_request::http_server_request(SoupMessage *message,
                               const std::string_view& path,
                               GHashTable *query,
                               SoupClientContext *client) noexcept :
            _message { message },
            _path { path }
    {
    }

    http_server_request::~http_server_request()
    {
    }

}
