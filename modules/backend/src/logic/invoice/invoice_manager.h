/**
 * @file invoice_manager.h
 * @author Feo
 * @date 07/11/2018
 * @brief
 */

#ifndef BACKEND_INVOICE_MANAGER_H
#define BACKEND_INVOICE_MANAGER_H

#include <engine.h>

#include "logic/invoice/pending_invoice.h"

namespace backend {

    class invoice_manager final {
    public:
        STL_DECLARE_SMARTPOINTERS(invoice_manager)

        invoice_manager();
        ~invoice_manager();

        pending_invoice *create(const stl::uuid& merchandise_guid,
                                std::string&& mail,
                                u64 amount,
                                SoupWebsocketConnection *connection) noexcept;

        pending_invoice *get_by_invoice_guid(const stl::uuid& invoice_guid) noexcept;
        pending_invoice *get_by_merchandise_guid(const stl::uuid& invoice_guid) noexcept;
        pending_invoice *get_by_connection(SoupWebsocketConnection *connection) noexcept;

        void disconnected(SoupWebsocketConnection *connection) noexcept;

    private:
        std::unordered_map<stl::uuid, pending_invoice *>                    _invoices_by_invoice_guid;
        std::unordered_map<stl::uuid, pending_invoice *>                    _invoices_by_merchandise_guid;
        std::unordered_map<SoupWebsocketConnection *, pending_invoice *>    _invoices_by_connection;

    };

}

#endif /* BACKEND_INVOICE_MANAGER_H */
