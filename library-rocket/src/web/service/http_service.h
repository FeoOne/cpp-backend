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
        FW_DECLARE_SMARTPOINTERS(http_service)
        FW_DELETE_ALL_DEFAULT(http_service)

        explicit http_service(const groot::config_setting::sptr& config,
                              const task_router::sptr& router,
                              const work_context_delegate *service_provider) noexcept;
        virtual ~http_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_http_response_task(const rocket::task::sptr& t) noexcept;

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
