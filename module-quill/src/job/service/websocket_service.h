/**
 * @file websocket_service.h
 * @author Feo
 * @date 23/08/2018
 * @brief
 */

#ifndef QUILL_WEBSOCKET_SERVICE_H
#define QUILL_WEBSOCKET_SERVICE_H

#include <rocket.h>

namespace quill {

    class websocket_service : public groot::crucial<rocket::work_service, websocket_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(websocket_service)
        GR_DELETE_ALL_DEFAULT(websocket_service)

        explicit websocket_service(const groot::config_setting::sptr& config,
                                   const rocket::task_router::sptr& router,
                                   const rocket::work_context_delegate *service_provider) noexcept;
        virtual ~websocket_service();

        void setup() noexcept final;
        void reset() noexcept final;


    private:

    };

}

#endif /* QUILL_WEBSOCKET_SERVICE_H */
