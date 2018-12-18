/**
 * @file ws_service.cpp
 * @author Feo
 * @date 23/08/2018
 * @brief
 */

#include "main/backend_consts.h"
#include "job/service/invoice_service.h"

#include "job/service/ws_service.h"

namespace backend {

    struct message_name {
        static constexpr const char *create_invoice { "create_invoice" };
    };

    ws_service::ws_service(const stl::setting& config,
                           engine::task_router *router,
                           const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _processors {}
    {
        EX_ASSIGN_TASK_HANDLER(engine::ws_request_task, ws_service, handle_ws_request_task);
        EX_ASSIGN_TASK_HANDLER(engine::ws_connection_status_task, ws_service, handle_ws_connection_status_task);

        _processors.insert({
            message_name::create_invoice,
            std::bind(&ws_service::process_create_invoice_message, this, std::placeholders::_1, std::placeholders::_2)
        });
    }

    // virtual
    ws_service::~ws_service()
    {
    }

    void ws_service::setup() noexcept
    {

    }

    void ws_service::reset() noexcept
    {

    }

    void ws_service::disconnect(SoupWebsocketConnection *ws) noexcept
    {
        auto task { new (std::nothrow) engine::ws_disconnect_task(ws) };
        router()->enqueue(task);
    }

    void ws_service::handle_ws_request_task(engine::basic_task *base_task) noexcept
    {
        static const size_t max_json_size { 256 };

        auto task { reinterpret_cast<engine::ws_request_task *>(base_task) };

        if (task->data_type() == SoupWebsocketDataType::SOUP_WEBSOCKET_DATA_BINARY) {
            // nothing there for the time beign
            logwarn("Received binary data from ws.");
            disconnect(task->connection());
        } else {
            gsize size { 0 };
            const char *text = task->text(&size);

            // basic checks
            if (text == nullptr || size > max_json_size) {
                disconnect(task->connection());
                return;
            }

            // parse json and process message
            try {
                Json::Value root;
                Json::CharReaderBuilder builder;
                auto reader { builder.newCharReader() };
                std::string errors;
                bool status { reader->parse(text, text + size, &root, &errors) };
                delete reader;

                if (!status) {
                    logwarn("Malformed json.");
                    disconnect(task->connection());
                    return;
                }

                auto name { root[consts::ws::name_key].asCString() };
                auto it { _processors.find(name) };
                if (it == _processors.end()) {
                    logwarn("Malformed json name: %s", name);
                    disconnect(task->connection());
                    return;
                }

                it->second(task->connection(), root);
            }
            catch (const std::exception& e) {
                logwarn("Failed to parse json: %s", e.what());
                disconnect(task->connection());
            }
        }
    }

    void ws_service::handle_ws_connection_status_task(engine::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<engine::ws_connection_status_task *>(base_task) };
        if (task->status() == engine::connection_status::disconnected) {
            delegate()->service<invoice_service>()->connection_disconnected(task->connection());
        }
    }

    /**
     * Create invoice request.
     * @param json
     * @return
     */
    void ws_service::process_create_invoice_message(SoupWebsocketConnection *connection,
                                                    const Json::Value& json) noexcept
    {
        delegate()->service<invoice_service>()->create_invoice(connection, json);
    }

}
