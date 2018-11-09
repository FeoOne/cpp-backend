/**
 * @file currency.h
 * @author Feo
 * @date 07/11/2018
 * @brief
 */

#ifndef BACKEND_CURRENCY_H
#define BACKEND_CURRENCY_H

#include <engine.h>

namespace backend::data {

    class currency {
    public:
        STL_DELETE_DEFAULT_CTOR(currency)

        static constexpr size_t ID_USD { 1 };
        static constexpr size_t ID_BTC { 2 };

        explicit currency(size_t id) noexcept : _id { id } {}

        size_t id() const noexcept { return _id; }
        void id(size_t val) noexcept { _id = val; }

        void from_name(const std::string_view& name) noexcept;

        static currency usd() noexcept {
            return currency { ID_USD };
        }

        static currency btc() noexcept {
            return currency { ID_BTC };
        }

    private:
        size_t          _id;

    };

}

#endif /* BACKEND_CURRENCY_H */
