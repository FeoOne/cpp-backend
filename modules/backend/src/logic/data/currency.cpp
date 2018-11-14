/**
 * @file currency.cpp
 * @author Feo
 * @date 08/11/2018
 * @brief
 */

#include "main/backend_consts.h"

#include "logic/data/currency.h"

namespace backend::data {

    // static
    currency currency::from_name(const std::string_view& name) noexcept
    {
        static std::map<std::string_view, size_t> map {
                { consts::currency::usd, id_usd },
                { consts::currency::btc, id_btc },
        };

        auto it = map.find(name);
        if (it != map.end()) {
            return currency { it->second };
        }

        return currency {};
    }

}
