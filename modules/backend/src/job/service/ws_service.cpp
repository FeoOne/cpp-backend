/**
 * @file ws_service.cpp
 * @author Feo
 * @date 23/08/2018
 * @brief
 */

#include "data/currency.h"

#include "job/service/ws_service.h"

namespace backend {

    static constexpr std::string_view create_invoice_message_name { "create_invoice" };

    ws_service::ws_service(const stl::setting& config,
                                         engine::task_router *router,
                                         const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _processors {}
    {
        EX_ASSIGN_TASK_HANDLER(engine::ws_request_task, ws_service, handle_ws_request_task);

        _processors.insert({
            create_invoice_message_name,
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
        router()->enqueue(engine::basic_task::create<engine::ws_disconnect_task>(ws));
    }

    void ws_service::handle_ws_request_task(engine::basic_task *base_task) noexcept
    {
        static const size_t max_json_size { 512 };

        auto task { reinterpret_cast<engine::ws_request_task *>(base_task) };

        if (task->data_type() == SoupWebsocketDataType::SOUP_WEBSOCKET_DATA_BINARY) {
            // nothing there for the time beign
            logwarn("Received binary data from ws.");
            disconnect(task->connection());
        } else {
            gsize size { 0 };
            const char *text = task->text(&size);
            lognotice("Text message from ws: %s", text);

            // basic checks
            if (text == nullptr || size > max_json_size) {
                disconnect(task->connection());
                return;
            }

            // parse json and process message
            try {
                Json::Value json { text };
                if (json.isMember("name")) {
                    _processors[json["name"].asCString()](task->connection(), json);
                } else {
                    logwarn("Malformed json: %s", text);
                    disconnect(task->connection());
                }

            }
            catch (const std::exception& e) {
                logwarn("Failed to parse json { %s } from client: %s", text, e.what());
                disconnect(task->connection());
            }
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
        if (!json.isMember("guid") || !json.isMember("guid")) {
            logwarn("Malformed json: %s", json.asCString());
            disconnect(connection);
            return;
        }

        stl::uuid merchandise_guid { json["guid"].asCString() };
        std::string email { json["mail"].asCString() };

        auto currency { data::currency::btc() };
        if (json.isMember("currency")) {
            currency.id(json["currency"].asUInt());
        }

        u64 amount { 0 };
        if (json.isMember("amount")) {
            amount = json["amount"].asUInt64();
        }

        // todo: validate incoming data

        auto invoice { new (std::nothrow) data::invoice(std::move(merchandise_guid),
                                                        std::move(email),
                                                        std::move(currency),
                                                        amount) };
        _invoice_manager->add(invoice);


        // todo: select merchandise, merchant, user
        // todo: create wallet
        // todo: create invoice
        // todo: respond
    }

}

#undef MAX_MESSAGE_SIZE
