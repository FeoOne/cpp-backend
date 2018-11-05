/**
 * @file websocket_service.cpp
 * @author Feo
 * @date 23/08/2018
 * @brief
 */

#include "job/service/websocket_service.h"

#define MAX_MESSAGE_SIZE    512

#define DISCONNECT(conn)    \
        router()->enqueue(engine::basic_task::create<engine::ws_disconnect_task>(conn))

namespace backend {

    static constexpr std::string_view create_invoice_message_name { "create_invoice" };

    websocket_service::websocket_service(const stl::setting& config,
                                         engine::task_router *router,
                                         const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _processors {}
    {
        EX_ASSIGN_TASK_HANDLER(engine::ws_request_task, websocket_service, handle_ws_request_task);

        _processors.insert({
            create_invoice_message_name,
            std::bind(&websocket_service::process_create_invoice_message, this, std::placeholders::_1)
        });
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

    void websocket_service::handle_ws_request_task(engine::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<engine::ws_request_task *>(base_task) };

        if (task->data_type() == SOUP_WEBSOCKET_DATA_BINARY) {
            // nothing there for the time beign
        } else {
            gsize size { 0 };
            const char *text = task->text(&size);
            lognotice("Text message from ws: %s", text);

            if (text == nullptr || size > MAX_MESSAGE_SIZE) {
                DISCONNECT(task->connection());
                return;
            }

            try {
                Json::Value root { text };
                _processors[root["name"].asCString()](root);
            }
            catch (std::exception& e) {
                logwarn("Failed to parse json from client: %s", e.what());
                DISCONNECT(task->connection());
            }
        }
    }

    engine::ws_response_task *
    websocket_service::process_create_invoice_message(Json::Value& json) noexcept
    {
//        auto msg = message::terra::create_invoice::make_shared(task->get_binary());
//
//        lognotice("amount: %s, currency: %lu", msg->get_amount().data(), msg->get_currency());

        //auto result = engine::ws_response_task::make_shared(task->connection(), )
        return nullptr;
    }

}
