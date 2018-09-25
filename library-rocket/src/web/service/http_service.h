/**
 * @file http_service.h
 * @author Feo
 * @date 18/08/2018
 * @brief
 */

#ifndef ROCKET_HTTP_SERVICE_H
#define ROCKET_HTTP_SERVICE_H

#include <libsoup/soup.h>

#include "work/work_service.h"

namespace rocket {

    class http_service final : public groot::crucial<work_service, http_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(http_service)
        GR_DELETE_ALL_DEFAULT(http_service)

        explicit http_service(const groot::setting& config,
                              task_router *router,
                              const work_service_delegate *service_delegate) noexcept;
        virtual ~http_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_http_response_task(basic_task *base_task) noexcept;

        void handler(SoupServer *server,
                     SoupMessage *message,
                     const char *path,
                     GHashTable *query,
                     SoupClientContext *client) noexcept;

        static void handler_routine(SoupServer *server,
                                    SoupMessage *message,
                                    const char *path,
                                    GHashTable *query,
                                    SoupClientContext *client,
                                    gpointer context) noexcept;

    };

}

#endif /* ROCKET_HTTP_SERVICE_H */
