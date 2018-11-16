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

    pending_invoice *invoice_manager::create(const stl::uuid& merchandise_guid,
                                             std::string&& mail,
                                             u64 amount,
                                             SoupWebsocketConnection *connection) noexcept
    {
        auto invoice { new (std::nothrow) pending_invoice(merchandise_guid, std::move(mail), amount) };
        invoice->assign_connection(connection);
        _invoices_by_merchandise_guid.insert({ invoice->guid(), invoice });
        _invoices_by_connection.insert({ connection, invoice });
        return invoice;
    }

    pending_invoice *invoice_manager::get_by_invoice_guid(const stl::uuid& invoice_guid) noexcept
    {
        pending_invoice *result { nullptr };
        auto it { _invoices_by_invoice_guid.find(invoice_guid) };
        if (it != _invoices_by_invoice_guid.end()) {
            result = it->second;
        }
        return result;
    }

    pending_invoice *invoice_manager::get_by_merchandise_guid(const stl::uuid &merchandise_guid) noexcept
    {
        pending_invoice *result { nullptr };
        auto it { _invoices_by_merchandise_guid.find(merchandise_guid) };
        if (it != _invoices_by_merchandise_guid.end()) {
            result = it->second;
        }
        return result;
    }

    pending_invoice *invoice_manager::get_by_connection(SoupWebsocketConnection *connection) noexcept
    {
        pending_invoice *result { nullptr };
        auto it { _invoices_by_connection.find(connection) };
        if (it != _invoices_by_connection.end()) {
            result = it->second;
        }
        return result;
    }

    void invoice_manager::disconnected(SoupWebsocketConnection *connection) noexcept
    {
        auto it { _invoices_by_connection.find(connection) };
        if (it != _invoices_by_connection.end()) {
            it->second->assign_connection(nullptr);
            _invoices_by_connection.erase(it);
        }
    }

}
