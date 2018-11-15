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

        pending_invoice *create(const stl::uuid& merchandise_guid, std::string&& mail, u64 amount) noexcept;
        pending_invoice *get_by_merchandise_guid(const stl::uuid &merchandise_guid) noexcept;

    private:
        std::unordered_map<stl::uuid, pending_invoice *>        _invoices_by_guid;

    };

}

#endif /* BACKEND_INVOICE_MANAGER_H */
