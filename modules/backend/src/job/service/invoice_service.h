/**
 * @file invoice_service.h
 * @author Feo
 * @date 19/12/2018
 * @brief
 */

#ifndef BACKEND_INVOICE_SERVICE_H
#define BACKEND_INVOICE_SERVICE_H

#include <engine.h>

#include "logic/invoice/invoice_manager.h"

namespace backend {

    class invoice_service final : public stl::crucial<engine::work_service, invoice_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(invoice_service)
        STL_DELETE_ALL_DEFAULT(invoice_service)

        explicit invoice_service(const stl::setting& config,
                                 engine::task_router *router,
                                 const engine::work_service_delegate *delegate) noexcept;

        virtual ~invoice_service();

        void setup() noexcept final;
        void reset() noexcept final;

        void connection_disconnected(SoupWebsocketConnection *connection) noexcept;

        void create_invoice(SoupWebsocketConnection *connection, const Json::Value& json) noexcept;

    private:
        invoice_manager::uptr                                       _invoice_manager;
        engine::timer::uptr                                         _invoice_poll_timer;

        void setup_invoice_poll_timer() noexcept;
        void reset_invoice_poll_timer() noexcept;

        void respond_invoice_created(pending_invoice *invoice) noexcept;

        // invoice polling
        void on_invoice_poll_timer() noexcept;
        void on_raw_mempool(const Json::Value& json) noexcept;
        void on_raw_transaction(const Json::Value& json) noexcept;

        // database responses
        void create_float_invoice_db_response_fn(engine::db_request *base_request) noexcept;

    };

}

#endif /* BACKEND_INVOICE_SERVICE_H */
