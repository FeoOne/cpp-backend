/**
 * @file websocket_service.h
 * @author Feo
 * @date 18/08/2018
 * @brief
 */

#ifndef ENGINE_WEBSOCKET_SERVICE_H
#define ENGINE_WEBSOCKET_SERVICE_H

#include <libsoup/soup.h>

#include "work/work_service.h"

namespace engine {

    class websocket_service final : public framework::crucial<work_service, websocket_service> {
    public:
        FW_DECLARE_SMARTPOINTERS(websocket_service)
        FW_DELETE_ALL_DEFAULT(websocket_service)

        explicit websocket_service(const framework::config_setting::sptr& config,
                                   const task_router::sptr& router,
                                   const work_context_delegate *service_provider) noexcept;
        virtual ~websocket_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handler(SoupServer *server,
                     SoupWebsocketConnection *connection,
                     const char *path,
                     SoupClientContext *client) noexcept;

        static void handler_routine(SoupServer *server,
                                    SoupWebsocketConnection *connection,
                                    const char *path,
                                    SoupClientContext *client,
                                    gpointer context) noexcept;

    };

}

#endif /* PROJECT_WEBSOCKET_SERVICE_H */
