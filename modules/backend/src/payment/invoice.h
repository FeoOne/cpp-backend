/**
 * @file invoice.h
 * @author Feo
 * @date 05/11/2018
 * @brief
 */

#ifndef BACKEND_INVOICE_H
#define BACKEND_INVOICE_H

#include <stl.h>

namespace backend {

    /**
     *
     */
    class invoice {
    public:
        STL_DELETE_ALL_DEFAULT(invoice)
        STL_DECLARE_SMARTPOINTERS(invoice)

        virtual ~invoice() = default;

        const stl::uuid& guid() const noexcept { return _guid; }
        const stl::uuid& merchandise_guid() const noexcept { return _merchandise_guid; }

    protected:
        explicit invoice(stl::uuid&& merchandise_guid, std::string_view&& email) noexcept :
                _guid { stl::uuid::generate_strategy::RANDOM },
                _merchandise_guid { merchandise_guid },
                _email { email }
        {}

        stl::uuid               _guid;
        stl::uuid               _merchandise_guid;
        std::string_view        _email;

    };

    /**
     *
     */
    class fixed_price_invoice : public invoice {
    public:
        STL_DELETE_ALL_DEFAULT(fixed_price_invoice)
        STL_DECLARE_SMARTPOINTERS(fixed_price_invoice)

        explicit fixed_price_invoice(stl::uuid&& merchandise_guid, std::string_view&& email) noexcept :
                invoice(std::move(merchandise_guid), std::move(email))
        {}

        virtual ~fixed_price_invoice() = default;

    private:

    };

    /**
     *
     */
    class floating_price_invoice : public invoice {
    public:
        STL_DELETE_ALL_DEFAULT(floating_price_invoice)
        STL_DECLARE_SMARTPOINTERS(floating_price_invoice)

        explicit floating_price_invoice(stl::uuid&& merchandise_guid, std::string_view&& email) noexcept :
                invoice(std::move(merchandise_guid), std::move(email))
        {}

        virtual ~floating_price_invoice() = default;

    private:

    };

}

#endif /* BACKEND_INVOICE_H */
