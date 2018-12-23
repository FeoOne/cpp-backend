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
                                             s64 amount,
                                             s64 fee,
                                             SoupWebsocketConnection *connection) noexcept
    {
        auto invoice { new (std::nothrow) pending_invoice(merchandise_guid, std::move(mail), amount, fee) };
        invoice->assign_connection(connection);
        _invoices_by_pending_guid.insert({ invoice->pending_guid(), invoice });
        _invoices_by_connection.insert({ connection, invoice });
        return invoice;
    }

    pending_invoice *invoice_manager::get_by_invoice_guid(const stl::uuid& invoice_guid) noexcept
    {
        pending_invoice *result { nullptr };
        const auto& it { _invoices_by_invoice_guid.find(invoice_guid) };
        if (it != _invoices_by_invoice_guid.end()) {
            result = it->second;
        }
        return result;
    }

    pending_invoice *invoice_manager::get_by_pending_guid(const stl::uuid &pending_guid) noexcept
    {
        pending_invoice *result { nullptr };
        const auto& it { _invoices_by_pending_guid.find(pending_guid) };
        if (it != _invoices_by_pending_guid.end()) {
            result = it->second;
        }
        return result;
    }

    pending_invoice *invoice_manager::get_by_connection(SoupWebsocketConnection *connection) noexcept
    {
        pending_invoice *result { nullptr };
        const auto& it { _invoices_by_connection.find(connection) };
        if (it != _invoices_by_connection.end()) {
            result = it->second;
        }
        return result;
    }

    pending_invoice *invoice_manager::get_by_address(const char *address) noexcept
    {
        pending_invoice *result { nullptr };
        const auto& it { _invoices_by_address.find(address) };
        if (it != _invoices_by_address.end()) {
            result = it->second;
        }
        return result;
    }

    void invoice_manager::remove(pending_invoice *invoice) noexcept
    {
        STL_SAFE_ERASE(_invoices_by_invoice_guid, invoice->guid());
        STL_SAFE_ERASE(_invoices_by_connection, invoice->connection());
        STL_SAFE_ERASE(_invoices_by_address, invoice->address());
    }

    void invoice_manager::on_created(pending_invoice *invoice) noexcept
    {
        STL_SAFE_ERASE(_invoices_by_pending_guid, invoice->pending_guid());

        _invoices_by_invoice_guid.insert({ invoice->guid(), invoice });
        _invoices_by_address.insert({ invoice->address(), invoice });
    }

    void invoice_manager::disconnected(SoupWebsocketConnection *connection) noexcept
    {
        const auto& it { _invoices_by_connection.find(connection) };
        if (it != _invoices_by_connection.end()) {
            it->second->assign_connection(nullptr);
            _invoices_by_connection.erase(it);
        }
    }

}
