/**
 * @file currency.h
 * @author Feo
 * @date 07/11/2018
 * @brief
 */

#ifndef BACKEND_CURRENCY_H
#define BACKEND_CURRENCY_H

#include <engine.h>

namespace backend {

    class currency {
    public:
        static constexpr size_t id_usd { 1 };
        static constexpr size_t id_btc { 2 };

        currency() : _id { id_usd } {}
        explicit currency(size_t id) noexcept : _id { id } {}

        size_t id() const noexcept { return _id; }

        static currency from_name(const std::string_view& name) noexcept;

        static currency usd() noexcept {
            return currency { id_usd };
        }

        static currency btc() noexcept {
            return currency { id_btc };
        }

    private:
        const size_t        _id;

    };

}

#endif /* BACKEND_CURRENCY_H */
