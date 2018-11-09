/**
 * @file constants.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef BACKEND_BACKEND_CONSTS_H
#define BACKEND_BACKEND_CONSTS_H

#include <stl.h>

namespace backend {

    struct consts {

        struct currency {
            static constexpr std::string_view usd { "usd" };
            static constexpr std::string_view btc { "btc" };
        };

        struct ws {
            static constexpr std::string_view name_key { "name" };
        };

        static constexpr std::string_view app_description { "- bitpayments backend server." };

    };

}

#endif /* BACKEND_BACKEND_CONSTS_H */
