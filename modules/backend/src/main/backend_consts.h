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

    class consts {
    public:
        static constexpr std::string_view   APP_DESCRIPTION     { "- bitpayments backend server." };

        static constexpr std::string_view   HTTP_INVOICE_PATH   { "/invoice" };

    };

}

#endif /* BACKEND_BACKEND_CONSTS_H */
