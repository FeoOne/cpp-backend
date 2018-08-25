/**
 * @file currency.h
 * @author Feo
 * @date 24/08/2018
 * @brief
 */

#ifndef MANTIS_CURRENCY_H
#define MANTIS_CURRENCY_H

namespace mantis {

    enum class currency_t {
        RAW = 0, // Fiat
        BTC = 1,
        ETH = 2,
        XMR = 3,
    };

}

#endif /* MANTIS_CURRENCY_H */
