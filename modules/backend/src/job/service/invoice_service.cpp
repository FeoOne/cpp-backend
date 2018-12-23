/**
 * @file invoice_service.cpp
 * @author Feo
 * @date 19/12/2018
 * @brief
 */

#include "main/backend_consts.h"
#include "job/service/ws_service.h"
#include "job/service/bitcoin_service.h"
#include "job/service/bitcoin_rpc_service.h"
#include "db/invoice_paid_db_request.h"
#include "db/invoice_create_float_db_request.h"

#include "job/service/invoice_service.h"

#define EX_INVOICE_POLL_TIMER_DELAY     1000
#define EX_INVOICE_POLL_TIMER_REPEAT    15000

namespace backend {

    invoice_service::invoice_service(const stl::setting& config,
                                     engine::task_router *router,
                                     const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _invoice_manager { invoice_manager::make_unique() },
            _invoice_poll_timer { engine::timer::make_unique() }
    {

    }

    // virtual
    invoice_service::~invoice_service()
    {
    }

    // virtual
    void invoice_service::setup() noexcept
    {
        setup_invoice_poll_timer();
    }

    // virtual
    void invoice_service::reset() noexcept
    {
        reset_invoice_poll_timer();
    }

    void invoice_service::setup_invoice_poll_timer() noexcept
    {
        _invoice_poll_timer->setup(delegate()->loop<engine::job_loop>()->loop(),
                                   EX_INVOICE_POLL_TIMER_DELAY,
                                   EX_INVOICE_POLL_TIMER_REPEAT,
                                   std::bind(&invoice_service::on_invoice_poll_timer, this));
        _invoice_poll_timer->start();
    }

    void invoice_service::reset_invoice_poll_timer() noexcept
    {
        _invoice_poll_timer->stop();
    }

    void invoice_service::connection_disconnected(SoupWebsocketConnection *connection) noexcept
    {
        _invoice_manager->disconnected(connection);
    }

    void invoice_service::create_invoice(SoupWebsocketConnection *connection, const Json::Value& json) noexcept
    {
        try {
            if (!json.isMember("guid") || !json.isMember("mail") || !json.isMember("amount")) {
                logwarn("Malformed json: %s", json.asCString());
                delegate()->service<ws_service>()->disconnect(connection);
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

            auto request { new (std::nothrow) invoice_create_float_db_request(invoice->pending_guid(),
                                                                              merchandise_guid,
                                                                              invoice->mail(),
                                                                              invoice->amount(),
                                                                              invoice->fee()) };
            request->assign_callback(std::bind(&invoice_service::invoice_create_float_db_response_fn,
                                               this,
                                               std::placeholders::_1));

            auto task { new (std::nothrow) engine::db_request_task(request) };
            router()->enqueue(task);
        }
        catch (const std::exception& e) {
            logwarn("Failed to process json: %s", e.what());
            delegate()->service<ws_service>()->disconnect(connection);
        }
    }

    void invoice_service::invoice_create_float_db_response_fn(engine::db_request *base_request) noexcept
    {
        auto request { reinterpret_cast<invoice_create_float_db_request *>(base_request) };
        if (request->is_success()) {
            auto invoice { _invoice_manager->get_by_pending_guid(request->pending_guid()) };
            if (invoice != nullptr) {
                invoice->on_created(request);
                _invoice_manager->on_created(invoice);

                if (invoice->connection() != nullptr) {
                    respond_invoice_created(invoice);
                }
            }
        }
    }

    void invoice_service::respond_invoice_created(pending_invoice *invoice) noexcept
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

    void invoice_service::on_invoice_poll_timer() noexcept
    {
        lognotice("Polling pending invoices...");

        BITCOIN_RPC_SERVICE->get_raw_mempool(false,
                                             std::bind(&invoice_service::on_raw_mempool,
                                                       this,
                                                       std::placeholders::_1));
    }

    void invoice_service::on_raw_mempool(const Json::Value& json) noexcept
    {
        if (!json["error"].isNull()) {
            logwarn("%s", json["error"].asCString());
            return;
        }

        auto& result { json["result"] };
        lognotice("Raw mempool tx count: %u.", result.size());
        for (const auto &i : result) {
            BITCOIN_RPC_SERVICE->get_raw_transaction(i.asCString(),
                                                     std::bind(&invoice_service::on_raw_transaction,
                                                               this,
                                                               std::placeholders::_1));
        }
    }

    void invoice_service::on_raw_transaction(const Json::Value& json) noexcept
    {
        if (!json["error"].isNull()) {
            logwarn("%s", json["error"].asCString());
            return;
        }

//        STL_PRINT_JSON(json);

        const auto& result { json["result"] };
        const auto& vout { result["vout"] };
        for (const auto &i : vout) {
            const auto& addresses { i["scriptPubKey"]["addresses"] };
            if (addresses.size() != 1) {
                continue;
            }

            auto invoice { _invoice_manager->get_by_address(addresses[0].asCString()) };
            if (invoice != nullptr) {
                const auto& txid { result["txid"].asString() };
                loginfo("Paid invoice guid: %s, address: %s, txid: %s.",
                        invoice->guid().to_string().data(),
                        invoice->address().data(),
                        txid.data());

                _invoice_manager->remove(invoice);
                invoice->on_paid(txid);

                auto request { new (std::nothrow) invoice_paid_db_request(invoice->guid(), txid) };
                auto task { new (std::nothrow) engine::db_request_task(request) };
                router()->enqueue(task);
            }
        }
    }

}
