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
            static constexpr const char *usd { "usd" };
            static constexpr const char *btc { "btc" };
        };

        struct ws {
            static constexpr const char *name_key { "name" };
        };

        struct config {
            struct key {
                static constexpr const char *bitcoin_rpc_address { "bitcoin_rpc_address" };
                static constexpr const char *bitcoin_rpc_credentials { "bitcoin_rpc_credentials" };
                static constexpr const char *bitcoin_fee_wait_blocks { "bitcoin_fee_wait_blocks" };
            };
        };

        static constexpr const char *app_description { "- bitpayments backend server." };

    };

}

#endif /* BACKEND_BACKEND_CONSTS_H */
