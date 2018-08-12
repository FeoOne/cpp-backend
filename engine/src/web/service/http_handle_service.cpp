/**
 * @file http_handle_service.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "web/service/http_handle_service.h"

namespace engine {

    http_handle_service::http_handle_service(SoupServer *server) noexcept :
            _server { server },
            _handlers {}
    {
    }

    // virtual
    http_handle_service::~http_handle_service()
    {

    }

    void http_handle_service::add_handler(const std::string_view& path,
                                          const http_request_handler::sptr& handler) noexcept
    {
        auto it = _handlers.find(path);
        if (it == _handlers.end()) {
            _handlers.insert({path, handler});
            soup_server_add_handler(_server, path.data(), &http_handle_service::_handler, this, nullptr);
        } else {
            logwarn("Can't add already added handler for path '%s'.", path.data());
        }
    }

    void http_handle_service::remove_handler(const std::string_view& path) noexcept
    {
        auto it = _handlers.find(path);
        if (it != _handlers.end()) {
            soup_server_remove_handler(_server, path.data());
            _handlers.erase(it);
        } else {
            logwarn("Can't remove non-exists handler for path '%s'.", path.data());
        }
    }

    void http_handle_service::_handler(SoupServer *server,
                                       SoupMessage *message,
                                       const char *path,
                                       GHashTable *query,
                                       SoupClientContext *client) noexcept
    {
        logdebug("HTTP handler fired. Host: %s, user: %s.",
                 soup_client_context_get_host(client),
                 soup_client_context_get_auth_user(client));

        http_response::sptr response { nullptr };

        auto it = _handlers.find({ path });
        if (it != _handlers.end()) {
            response = it->second->handle(nullptr);
        } else {
            logwarn("No handler presented for path '%s'.");

            // @todo Setup default error response
        }

        // @todo Process response
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
