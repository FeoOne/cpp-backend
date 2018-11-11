/**
 * @file invoice.h
 * @author Feo
 * @date 05/11/2018
 * @brief
 */

#ifndef BACKEND_INVOICE_H
#define BACKEND_INVOICE_H

#include <libsoup/soup.h>

#include <stl.h>

#include "data/currency.h"
#include "db/select_merchandise_data_db_request.h"

namespace backend::data {

    /**
     *
     */
    class invoice {
    public:
        STL_DELETE_ALL_DEFAULT(invoice)
        STL_DECLARE_SMARTPOINTERS(invoice)

        explicit invoice(SoupWebsocketConnection *connection,
                         const stl::uuid& merchandise_guid,
                         std::string&& email,
                         const data::currency& currency,
                         u64 amount) noexcept :
                _connection { connection },
                _guid { stl::uuid::generate_strategy::RANDOM },
                _merchandise_guid { merchandise_guid },
                _email { email },
                _currency { currency },
                _amount { amount }
        {}

        ~invoice() = default;

        SoupWebsocketConnection *connection() noexcept { return _connection; }
        const stl::uuid& guid() const noexcept { return _guid; }
        const stl::uuid& merchandise_guid() const noexcept { return _merchandise_guid; }
        const std::string& email() const noexcept { return _email; }
        const data::currency& currency() const noexcept { return _currency; }
        u64 amount() const noexcept { return _amount; }
        const char *address() const noexcept { return _address; }

        const std::string& merchant_label() const noexcept { return _merchant_label; }
        const std::string& merchandise_label() const noexcept { return _merchandise_label; }

        void update(select_merchandise_data_db_request *request) noexcept;

    private:
        SoupWebsocketConnection *   _connection;
        stl::uuid                   _guid;
        stl::uuid                   _merchandise_guid;
        std::string                 _email;
        data::currency              _currency;
        u64                         _amount;
        char                        _address[64];

        std::string                 _merchant_label;
        std::string                 _merchandise_label;

    };

}

#endif /* BACKEND_INVOICE_H */
