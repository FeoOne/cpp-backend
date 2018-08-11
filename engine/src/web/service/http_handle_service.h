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

namespace engine {

    class http_handle_service : public basic_execution_service<http_handle_service> {
    public:
        FW_DECLARE_SMARTPOINTERS(http_handle_service)
        FW_DELETE_ALL_DEFAULT(http_handle_service)

        explicit http_handle_service(SoupServer *server) noexcept;
        virtual ~http_handle_service();

    private:
        SoupServer *            _server;

        void _handler(SoupServer *server,
                      SoupMessage *message,
                      const char *path,
                      GHashTable *query,
                      SoupClientContext *client) noexcept;

        static void _handler(SoupServer *server,
                             SoupMessage *message,
                             const char *path,
                             GHashTable *query,
                             SoupClientContext *client,
                             gpointer context) noexcept;

    };

}

#endif /* ENGINE_HTTP_HANDLE_SERVICE_H */
