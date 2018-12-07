/**
 * @file http_service.h
 * @author Feo
 * @date 18/08/2018
 * @brief
 */

#ifndef ENGINE_HTTP_SERVICE_H
#define ENGINE_HTTP_SERVICE_H

#include <libsoup/soup.h>

#include "work/service/work_service.h"

namespace engine {

    /**
     * HTTP server service is for accepting http requests.
     * This class represents basic HTTP server.
     */
    class http_server_service final : public stl::crucial<work_service, http_server_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(http_server_service)
        STL_DELETE_ALL_DEFAULT(http_server_service)

        explicit http_server_service(const stl::setting& config,
                              task_router *router,
                              const work_service_delegate *delegate) noexcept;
        virtual ~http_server_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_http_response_task(basic_task *base_task) noexcept;

        void handler(SoupServer *server,
                     SoupMessage *message,
                     const char *path,
                     GHashTable *query,
                     SoupClientContext *client) noexcept;

        static void handler_callback(SoupServer *server,
                                    SoupMessage *message,
                                    const char *path,
                                    GHashTable *query,
                                    SoupClientContext *client,
                                    gpointer context) noexcept;

    };

}

#endif /* ENGINE_HTTP_SERVICE_H */
