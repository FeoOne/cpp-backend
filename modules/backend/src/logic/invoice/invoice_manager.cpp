/**
 * @file invoice_manager.cpp
 * @author Feo
 * @date 07/11/2018
 * @brief
 */

#include "logic/invoice/invoice_manager.h"

namespace backend {

    invoice_manager::invoice_manager()
    {

    }

    invoice_manager::~invoice_manager()
    {

    }

    pending_invoice *invoice_manager::create(const stl::uuid& merchandise_guid, std::string&& mail) noexcept
    {
        auto invoice { new (std::nothrow) pending_invoice(merchandise_guid, std::move(mail)) };
        _invoices_by_guid.insert({ invoice->guid(), invoice });
        return invoice;
    }

    pending_invoice *invoice_manager::get(const stl::uuid& invoice_guid) noexcept
    {
//        data::invoice *result { nullptr };
//
//        STL_UNIQUE_LOCK(lock, _mutex);
//
//        auto it { _invoices_by_guid.find(invoice_guid) };
//        if (it != _invoices_by_guid.end()) {
//            result = it->second;
//        }
//
//        return result;
    }

}
