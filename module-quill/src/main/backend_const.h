/**
 * @file constants.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef BACKEND_CONSTANTS_H
#define BACKEND_CONSTANTS_H

#include <framework.h>

namespace backend {

    class backend_const {
    public:
        static constexpr std::string_view   APP_DESCRIPTION     { "- bitpayments backend server." };

        static constexpr std::string_view   HTTP_INVOICE_PATH   { "/invoice" };

    };

}

#endif /* BACKEND_CONSTANTS_H */
