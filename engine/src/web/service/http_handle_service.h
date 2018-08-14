/**
 * @file http_handle_service.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_HTTP_HANDLE_SERVICE_H
#define ENGINE_HTTP_HANDLE_SERVICE_H

#include <libsoup/soup.h>

#include "web/service/web_server_service.h"

namespace engine {

    /**
     *
     */
    class http_handle_service final : public web_server_service<http_handle_service> {
    public:
        FW_DECLARE_SMARTPOINTERS(http_handle_service)
        FW_DELETE_ALL_DEFAULT(http_handle_service)

        explicit http_handle_service(const event_router::sptr& router, SoupServer *server) noexcept;
        virtual ~http_handle_service();

    private:
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
