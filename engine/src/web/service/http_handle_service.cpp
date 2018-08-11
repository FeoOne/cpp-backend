/**
 * @file http_handle_service.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "web/service/http_handle_service.h"

namespace engine {

    http_handle_service::http_handle_service(SoupServer *server) :
            _server { server }
    {
        soup_server_add_handler(_server, nullptr, &http_handle_service::_handler, this, nullptr);
    }

    // virtual
    http_handle_service::~http_handle_service()
    {
        soup_server_remove_handler(_server, nullptr);
    }

    void http_handle_service::_handler(SoupServer *server,
                                       SoupMessage *message,
                                       const char *path,
                                       GHashTable *query,
                                       SoupClientContext *client) noexcept
    {
        logdebug("HTTP handler fired.");

        // @todo
    }

    // static
    void http_handle_service::_handler(SoupServer *server,
                                       SoupMessage *message,
                                       const char *path,
                                       GHashTable *query,
                                       SoupClientContext *client,
                                       gpointer context) noexcept
    {
        auto self = static_cast<http_handle_service *>(context);
        self->_handler(server, message, path, query, client);
    }

}
