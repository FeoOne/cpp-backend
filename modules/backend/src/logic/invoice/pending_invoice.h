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

        explicit pending_invoice(const stl::uuid& merchandise_guid, std::string&& mail, s64 amount, s64 fee) noexcept;
        ~pending_invoice();

        u64 id() const noexcept { return _id; }
        const stl::uuid& guid() const noexcept { return _guid; }
        const stl::uuid& pending_guid() const noexcept { return _pending_guid; }
        const stl::uuid& wallet_guid() const noexcept { return _wallet_guid; }

        const std::string& address() const noexcept { return _address; }

        const stl::uuid& merchandise_guid() const noexcept { return _merchandise_guid; }
        const std::string& mail() const noexcept { return _mail; }
        s64 amount() const noexcept { return _amount; }

        s64 fee() const noexcept { return _fee; }

        void update(create_float_invoice_db_request *request) noexcept;

        void assign_connection(SoupWebsocketConnection *connection) noexcept { _connection = connection; }
        SoupWebsocketConnection *connection() noexcept { return _connection; }

    private:
        pending_state               _state;

        u64                         _id;
        stl::uuid                   _guid;
        stl::uuid                   _pending_guid;
        stl::uuid                   _wallet_guid;
        u32                         _confirm_block_count;
        std::string                 _callback_url;
        std::string                 _address;

        stl::uuid                   _merchandise_guid;
        std::string                 _mail;
        s64                         _amount;

        s64                         _fee;

        SoupWebsocketConnection *   _connection;

    };

}

#endif /* BACKEND_PENDING_INVOICE_H */
