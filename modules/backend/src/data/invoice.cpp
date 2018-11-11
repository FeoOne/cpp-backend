/**
 * @file invoice.cpp
 * @author Feo
 * @date 05/11/2018
 * @brief
 */

#include <btc/bip32.h>
#include <btc/utils.h>

#include "data/invoice.h"

namespace backend::data {

    void invoice::update(select_merchandise_data_db_request *request) noexcept
    {
        _merchant_label.assign(request->merchant_label);
        _merchandise_label.assign(request->merchandise_label);

        btc_hdnode node;
        auto chainparams {
#ifdef NDEBUG
            &btc_chainparams_main
#else
            &btc_chainparams_test
#endif
        };

        btc_hdnode_from_seed(utils_hex_to_uint8(request->private_key), 32, &node);

//        lognotice("chain code: %s", utils_uint8_to_hex(node.chain_code, 32));
//        lognotice("private key: %s", utils_uint8_to_hex(node.private_key, 32));
//
//        btc_hdnode_serialize_private(&node, chainparams, str, sizeof(str));
//        lognotice("master: %s", str);

        btc_hdnode_get_p2pkh_address(&node, chainparams, _address, sizeof(_address));
        lognotice("Genrated p2pkh address: %s", _address);
    }

}
