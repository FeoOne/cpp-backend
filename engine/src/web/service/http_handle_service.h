/**
 * @file http_handle_service.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_HTTP_HANDLE_SERVICE_H
#define ENGINE_HTTP_HANDLE_SERVICE_H

#include <libsoup/soup.h>

#include "core/execution_service.h"
#include "web/http/http_request_handler.h"

namespace engine {

    /**
     *
     */
    class http_handle_service : public framework::crucial<http_handle_service, execution_service> {
    public:
        FW_DECLARE_SMARTPOINTERS(http_handle_service)
        FW_DELETE_ALL_DEFAULT(http_handle_service)

        explicit http_handle_service(SoupServer *server) noexcept;
        virtual ~http_handle_service();

        void add_handler(const std::string_view& path, const http_request_handler::sptr& handler) noexcept;
        void remove_handler(const std::string_view& path) noexcept;

    private:
        using handler_map = std::unordered_map<std::string_view, http_request_handler::sptr>;

        SoupServer *            _server;
        handler_map             _handlers;

        void handler(SoupServer *server,
                     SoupMessage *message,
                     const char *path,
                     GHashTable *query,
                     SoupClientContext *client) noexcept;

        static void handler(SoupServer *server,
                            SoupMessage *message,
                            const char *path,
                            GHashTable *query,
                            SoupClientContext *client,
                            gpointer context) noexcept;

    };

}

#endif /* ENGINE_HTTP_HANDLE_SERVICE_H */
