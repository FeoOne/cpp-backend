/**
 * @file pending_invoice.h
 * @author Feo
 * @date 14/11/2018
 * @brief
 */

#ifndef BACKEND_PENDING_INVOICE_H
#define BACKEND_PENDING_INVOICE_H

#include <stl.h>

#include "db/create_float_invoice_db_request.h"

namespace backend {

    class pending_invoice {
    public:
        enum class pending_state {
            initialized,
            created,
            paid,
            confirmed,
        };

        explicit pending_invoice(const stl::uuid& merchandise_guid, std::string&& mail, u64 amount) noexcept;
        ~pending_invoice();

        u64 id() const noexcept { return _id; }
        const stl::uuid& guid() const noexcept { return _guid; }
        const stl::uuid& wallet_guid() const noexcept { return _wallet_guid; }

        const stl::uuid& merchandise_guid() const noexcept { return _merchandise_guid; }
        const char *mail() const noexcept { return _mail.data(); }

        u64 amount() const noexcept { return _amount; }

        void update(create_float_invoice_db_request *request) noexcept;

    private:
        pending_state               _state;

        u64                         _id;
        stl::uuid                   _guid;
        stl::uuid                   _wallet_guid;
        u32                         _confirm_block_count;
        char *                      _callback_url;

        stl::uuid                   _merchandise_guid;
        std::string                 _mail;
        u64                         _amount;

        void generate_address() noexcept;

    };

}

#endif /* BACKEND_PENDING_INVOICE_H */
