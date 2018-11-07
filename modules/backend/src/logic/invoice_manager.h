/**
 * @file invoice_manager.h
 * @author Feo
 * @date 07/11/2018
 * @brief
 */

#ifndef BACKEND_INVOICE_MANAGER_H
#define BACKEND_INVOICE_MANAGER_H

#include <engine.h>

#include "data/invoice.h"

namespace backend {

    class invoice_manager final {
    public:
        STL_DECLARE_SMARTPOINTERS(invoice_manager)

        invoice_manager();
        ~invoice_manager();

        void add(data::invoice *invoice) noexcept;

    private:
        mutable std::timed_mutex    _mutex;

        std::unordered_map<stl::uuid, data::invoice *>      _invoices_by_guid;

    };

}

#endif /* BACKEND_INVOICE_MANAGER_H */
