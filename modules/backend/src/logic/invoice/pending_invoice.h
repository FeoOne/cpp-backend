/**
 * @file pending_invoice.h
 * @author Feo
 * @date 14/11/2018
 * @brief
 */

#ifndef BACKEND_PENDING_INVOICE_H
#define BACKEND_PENDING_INVOICE_H

#include <stl.h>

#include "logic/data/currency.h"

namespace backend {

    class pending_invoice {
    public:
        enum class pending_state {
            created,
            filled,
            paid,
            confirmed,
        };

        explicit pending_invoice(const stl::uuid& merchandise_guid, std::string&& mail) noexcept;
        ~pending_invoice() = default;

        const stl::uuid& guid() const noexcept { return _guid; }
        const stl::uuid& merchandise_guid() const noexcept { return _merchandise_guid; }

        void set_currency(const currency& cy) noexcept { _cy = cy; }
        void set_amount(u64 amount) noexcept { _amount = amount; }

    private:
        pending_state               _state;

        stl::uuid                   _guid;
        stl::uuid                   _merchandise_guid;
        std::string                 _mail;
        currency                    _cy;
        u64                         _amount;

    };

}

#endif /* BACKEND_PENDING_INVOICE_H */
