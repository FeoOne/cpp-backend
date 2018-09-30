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

        explicit websocket_service(const groot::setting& config,
                                   rocket::task_router *router,
                                   const rocket::work_service_delegate *delegate) noexcept;
        virtual ~websocket_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        using message_processor =
                std::function<rocket::ws_outgoing_message_task *(const rocket::ws_incoming_message_task *)>;

        std::unordered_map<u32, message_processor>      _processors;

        void handle_ws_incoming_message_task(rocket::basic_task *base_task) noexcept;

        rocket::ws_outgoing_message_task *
        process_create_invoice_message(rocket::ws_incoming_message_task *task) noexcept;

    };

}

#endif /* QUILL_WEBSOCKET_SERVICE_H */
