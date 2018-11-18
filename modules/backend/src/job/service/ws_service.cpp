/**
 * @file ws_service.cpp
 * @author Feo
 * @date 23/08/2018
 * @brief
 */

#include "main/backend_consts.h"
#include "job/service/bitcoin_service.h"
#include "job/service/bitcoin_rpc_service.h"
#include "db/create_float_invoice_db_request.h"

#include "job/service/ws_service.h"

#define EX_INVOICE_POLL_TIMER_DELAY     1000
#define EX_INVOICE_POLL_TIMER_REPEAT    15000

namespace backend {

    static constexpr std::string_view create_invoice_message_name { "create_invoice" };

    ws_service::ws_service(const stl::setting& config,
                           engine::task_router *router,
                           const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _processors {},
            _invoice_manager { invoice_manager::make_unique() },
            _invoice_poll_timer { engine::timer::make_unique() }
    {
        EX_ASSIGN_TASK_HANDLER(engine::ws_request_task, ws_service, handle_ws_request_task);
        EX_ASSIGN_TASK_HANDLER(engine::ws_connection_status_task, ws_service, handle_ws_connection_status_task);

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
        _invoice_poll_timer->setup(delegate()->loop<engine::job_loop>()->loop(),
                                   EX_INVOICE_POLL_TIMER_DELAY,
                                   EX_INVOICE_POLL_TIMER_REPEAT,
                                   std::bind(&ws_service::on_invoice_poll_timer, this));
        _invoice_poll_timer->start();
    }

    void ws_service::reset() noexcept
    {
        _invoice_poll_timer->stop();
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
            _invoice_manager->disconnected(task->connection());
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
            s64 amount { json["amount"].asInt64() };

            auto invoice { _invoice_manager->create(merchandise_guid,
                                                    std::move(mail),
                                                    amount,
                                                    BITCOIN_SERVICE->estimated_fee(),
                                                    connection) };

            auto request { new (std::nothrow) create_float_invoice_db_request(invoice->pending_guid(),
                                                                              merchandise_guid,
                                                                              invoice->mail(),
                                                                              invoice->amount(),
                                                                              invoice->fee()) };
            request->assign_callback(std::bind(&ws_service::create_float_invoice_db_response_fn,
                                               this,
                                               std::placeholders::_1));

            auto task { new (std::nothrow) engine::db_request_task(request) };
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
            auto invoice { _invoice_manager->get_by_pending_guid(request->pending_guid()) };
            if (invoice != nullptr) {
                invoice->update(request);

                if (invoice->connection() != nullptr) {
                    respond_invoice_created(invoice);
                }
            }
        }
    }

    void ws_service::respond_invoice_created(pending_invoice *invoice) noexcept
    {
        Json::Value root;
        root["name"] = "invoice_created";
        root["address"] = invoice->address();
        root["amount"] = invoice->amount();
        root["fee"] = invoice->fee();
        root["invoice_guid"] = invoice->guid().to_string();

        Json::StreamWriterBuilder builder;
        auto data { Json::writeString(builder, root) };

        auto task { new (std::nothrow) engine::ws_response_task(invoice->connection(), std::move(data)) };
        router()->enqueue(task);
    }

    void ws_service::on_invoice_poll_timer() noexcept
    {
        lognotice("Polling pending invoices...");

        Json::Value mempool;
        if (!BITCOIN_RPC_SERVICE->get_raw_mempool(false, mempool)) {
            return;
        }

        if (!mempool["error"].isNull()) {
            logwarn("%s", mempool["error"].asCString());
            return;
        }

        //for (const auto& txid: mempool["result"]) {
        auto& result { mempool["result"] };
        for (Json::Value::ArrayIndex i = 0; i < result.size(); ++i) {
            logdebug("txid: %s", result[i].asCString());

            Json::Value tx;
            if (!BITCOIN_RPC_SERVICE->get_raw_transaction(result[i].asCString(), tx)) {
                continue;
            }

            if (!tx["error"].isNull()) {
                logwarn("%s", tx["error"].asCString());
                continue;
            }

            auto& address { tx["result"]["vout"][0]["scriptPubKey"]["addresses"][0] };
            if (address.isNull()) {
                continue;
            }

            logdebug("address: %s", address.asCString());

//            try {
//
//            }
//            catch (const std::exception& e) {
//                logwarn("%s", e.what());
//
//                Json::StreamWriterBuilder write_builder;
//                auto data { Json::writeString(write_builder, tx) };
//                printf("%s\n\n", data.data());
//            }
        }

//        auto& result { mempool["result"] };
//        for (auto it { result.begin() }; it != result.end(); ++it) {
//            auto key = it.key();
//            auto value = (*it);
//        }








//        for (const auto& json : mempool["result"]) {
//            const Json::StaticString& k = json.first;
//            Json::Value& v = json.second;
//
//            Json::StreamWriterBuilder write_builder;
//            auto data { Json::writeString(write_builder, json) };
//            printf("%s\n\n", data.data());
//        }
//
//        for (auto& pair: _invoice_manager->invoices_by_invoice_guid()) {
//            auto invoice { pair.second };
//
//
//        }
    }

}
