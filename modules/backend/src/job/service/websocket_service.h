/**
 * @file websocket_service.h
 * @author Feo
 * @date 23/08/2018
 * @brief
 */

#ifndef BACKEND_WEBSOCKET_SERVICE_H
#define BACKEND_WEBSOCKET_SERVICE_H

#include <engine.h>

namespace backend {

    class websocket_service : public stl::crucial<engine::work_service, websocket_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(websocket_service)
        STL_DELETE_ALL_DEFAULT(websocket_service)

        explicit websocket_service(const stl::setting& config,
                                   engine::task_router *router,
                                   const engine::work_service_delegate *delegate) noexcept;
        virtual ~websocket_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        using message_processor =
                std::function<engine::ws_outgoing_message_task *(const engine::ws_incoming_message_task *)>;

        std::unordered_map<u32, message_processor>      _processors;

        void handle_ws_incoming_message_task(engine::basic_task *base_task) noexcept;

        engine::ws_outgoing_message_task *
        process_create_invoice_message(engine::ws_incoming_message_task *task) noexcept;

    };

}

#endif /* BACKEND_WEBSOCKET_SERVICE_H */
