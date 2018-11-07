/**
 * @file invoice.h
 * @author Feo
 * @date 05/11/2018
 * @brief
 */

#ifndef BACKEND_INVOICE_H
#define BACKEND_INVOICE_H

#include <stl.h>

#include "data/currency.h"

namespace backend::data {

    /**
     *
     */
    class invoice {
    public:
        STL_DELETE_ALL_DEFAULT(invoice)
        STL_DECLARE_SMARTPOINTERS(invoice)

        explicit invoice(stl::uuid&& merchandise_guid,
                         std::string&& email,
                         data::currency&& currency,
                         u64 amount) noexcept :
                _guid { stl::uuid::generate_strategy::RANDOM },
                _merchandise_guid { merchandise_guid },
                _email { email },
                _currency { currency },
                _amount { amount }
        {}

        ~invoice() = default;

        const stl::uuid& guid() const noexcept { return _guid; }
        const stl::uuid& merchandise_guid() const noexcept { return _merchandise_guid; }
        const std::string& email() const noexcept { return _email; }
        const data::currency& currency() const noexcept { return _currency; }
        u64 amount() const noexcept { return _amount; }

    private:
        stl::uuid               _guid;
        stl::uuid               _merchandise_guid;
        std::string             _email;
        data::currency          _currency;
        u64                     _amount;

    };

}

#endif /* BACKEND_INVOICE_H */
