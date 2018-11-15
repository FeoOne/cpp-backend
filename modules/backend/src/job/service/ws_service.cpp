/**
 * @file ws_service.cpp
 * @author Feo
 * @date 23/08/2018
 * @brief
 */

#include "main/backend_consts.h"
#include "bitcoin/bitcoin.h"
#include "db/create_float_invoice_db_request.h"

#include "job/service/ws_service.h"

namespace backend {

    static constexpr std::string_view create_invoice_message_name { "create_invoice" };

    ws_service::ws_service(const stl::setting& config,
                                         engine::task_router *router,
                                         const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _processors {},
            _invoice_manager { invoice_manager::make_unique() }
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
        static const size_t max_json_size { 256 };

        auto task { reinterpret_cast<engine::ws_request_task *>(base_task) };

        if (task->data_type() == SoupWebsocketDataType::SOUP_WEBSOCKET_DATA_BINARY) {
            // nothing there for the time beign
            logwarn("Received binary data from ws.");
            disconnect(task->connection());
        } else {
            gsize size { 0 };
            const char *text = task->text(&size);
            logdebug("Text message from ws: %s", text);

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

    /**
     * Create invoice request.
     * @param json
     * @return
     */
    void ws_service::process_create_invoice_message(SoupWebsocketConnection *connection,
                                                    const Json::Value& json) noexcept
    {
        try {
            if (!json.isMember("guid") || !json.isMember("mail") || !json.isMember("amount")) {
                logwarn("Malformed json: %s", json.asCString());
                disconnect(connection);
                return;
            }

            stl::uuid merchandise_guid { json["guid"].asCString() };
            std::string mail { json["mail"].asCString() };
            u64 amount { json["amount"].asUInt64() };

            auto invoice { _invoice_manager->create(merchandise_guid, std::move(mail), amount) };
            auto request { engine::db_request::create<create_float_invoice_db_request>(merchandise_guid,
                                                                                       invoice->mail(),
                                                                                       invoice->amount()) };
            request->assign_callback(std::bind(&ws_service::create_float_invoice_db_response_fn,
                                               this,
                                               std::placeholders::_1));

            auto task { engine::basic_task::create<engine::db_request_task>(request) };
            router()->enqueue(task);
        }
        catch (const std::exception& e) {
            logwarn("Failed to process json: %s", e.what());
            disconnect(connection);
        }
    }

    void ws_service::create_float_invoice_db_response_fn(engine::db_request *base_request) noexcept
    {
        auto request { reinterpret_cast<create_float_invoice_db_request *>(base_request) };
        if (request->is_success()) {
            auto invoice { _invoice_manager->get_by_merchandise_guid(request->merchandise_guid) };
            if (invoice != nullptr) {
                invoice->update(request);

                Json::Value root;
                root["name"] = "invoice_created";
                root["address"] = bitcoin::generate_address(invoice->wallet_guid().data(),
                                                            stl::uuid::size,
                                                            invoice->id());
                root["amount"] = invoice->amount();

                Json::StreamWriterBuilder builder;
                auto json { Json::writeString(builder, root) };

                auto task { engine::basic_task::create<engine::ws_response_task>(invoice->connection(),
                                                                                 std::move(json)) };
                router()->enqueue(task);
            }
        }
    }

}
