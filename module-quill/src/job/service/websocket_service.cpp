/**
 * @file websocket_service.cpp
 * @author Feo
 * @date 23/08/2018
 * @brief
 */

//#include "message/message_terra_gen.h"

#include "job/service/websocket_service.h"

namespace quill {

    websocket_service::websocket_service(const groot::setting& config,
                                         rocket::task_router *router,
                                         const rocket::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _processors {}
    {
        RC_ASSIGN_TASK_HANDLER(rocket::ws_incoming_message_task, websocket_service, handle_ws_incoming_message_task);

//        _processors.insert({
//            OPCODE_MESSAGE_TERRA_CREATE_INVOICE,
//            std::bind(&websocket_service::process_create_invoice_message, this, std::placeholders::_1)
//        });
    }

    // virtual
    websocket_service::~websocket_service()
    {
    }

    void websocket_service::setup() noexcept
    {

    }

    void websocket_service::reset() noexcept
    {

    }

    void websocket_service::handle_ws_incoming_message_task(rocket::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<rocket::ws_incoming_message_task *>(base_task) };

        if (task->get_data_type() == SOUP_WEBSOCKET_DATA_BINARY) {
            lognotice("magic: 0x%lX, opcode: %lu, length: %lu",
                    task->get_header()->get_magic(),
                    task->get_header()->get_opcode(),
                    task->get_header()->get_length());
            if (task->get_header()->get_magic() == rocket::consts::PROTOCOL_MAGIC) {
                // @todo Version check
                auto result { _processors[task->get_header()->get_opcode()](task) };
                if (result != nullptr) {
                    router()->enqueue(result);
                }
            }
        } else {
            gsize sz;
            gconstpointer ptr = g_bytes_get_data(task->get_bytes(), &sz);
            lognotice("Text message from ws: %s", ptr);
        }
    }

    rocket::ws_outgoing_message_task *
    websocket_service::process_create_invoice_message(rocket::ws_incoming_message_task *task) noexcept
    {
//        auto msg = message::terra::create_invoice::make_shared(task->get_binary());
//
//        lognotice("amount: %s, currency: %lu", msg->get_amount().data(), msg->get_currency());

        //auto result = rocket::ws_outgoing_message_task::make_shared(task->get_connection(), )
        return nullptr;
    }

}
