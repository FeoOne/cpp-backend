/**
 * @file bitcoin.cpp
 * @author Feo
 * @date 15/11/2018
 * @brief
 */

#include <btc/bip32.h>
#include <btc/utils.h>

#include "bitcoin/bitcoin.h"

namespace backend {

    static const btc_chainparams *chain {
#ifdef NDEBUG
            &btc_chainparams_main
#else
            &btc_chainparams_test
#endif
    };

    // static
    std::string bitcoin::generate_address(const u8 *seed, size_t seed_size, u64 index) noexcept
    {
        char result[64];
        char path[16];
        std::snprintf(path, sizeof(path), "m/0/%llu", index);

        btc_hdnode node;
        btc_hdnode_from_seed(seed, static_cast<int>(seed_size), &node);
        btc_hd_generate_key(&node, path, node.private_key, node.chain_code, 0);
        btc_hdnode_get_p2pkh_address(&node, chain, result, sizeof(result));

        return { result };
    }

    // static
    s64 bitcoin::json_value_to_amount(double value) noexcept
    {
        return static_cast<s64>(value * 1e8 + (value < 0.0 ? -0.5 : 0.5));
    }

    // static
    double bitcoin::amount_to_json_value(s64 amount) noexcept
    {
        return static_cast<double>(amount) / 1e8;
    }

}
