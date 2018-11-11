/**
 * @file currency.cpp
 * @author Feo
 * @date 08/11/2018
 * @brief
 */

#include "main/backend_consts.h"

#include "data/currency.h"

namespace backend::data {

    void currency::from_name(const std::string_view& name) noexcept
    {
        static std::map<std::string_view, size_t> map {
                { consts::currency::usd, ID_USD },
                { consts::currency::btc, ID_BTC },
        };

        auto it = map.find(name);
        if (it != map.end()) {
            _id = it->second;
        }
    }

}
