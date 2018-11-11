/**
 * @file invoice_manager.cpp
 * @author Feo
 * @date 07/11/2018
 * @brief
 */

#include "logic/invoice_manager.h"

namespace backend {

    invoice_manager::invoice_manager()
    {

    }

    invoice_manager::~invoice_manager()
    {

    }

    void invoice_manager::add(data::invoice *invoice) noexcept
    {
        STL_UNIQUE_LOCK(lock, _mutex);

        auto it { _invoices_by_guid.find(invoice->guid()) };
        if (it == _invoices_by_guid.end()) {
            _invoices_by_guid.insert({ invoice->guid(), invoice });
        }
    }

    data::invoice *invoice_manager::get(const stl::uuid& invoice_guid) noexcept
    {
        data::invoice *result { nullptr };

        STL_UNIQUE_LOCK(lock, _mutex);

        auto it { _invoices_by_guid.find(invoice_guid) };
        if (it != _invoices_by_guid.end()) {
            result = it->second;
        }

        return result;
    }

}
