/**
 * @file constants.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef QUILL_QUILL_CONSTS_H
#define QUILL_QUILL_CONSTS_H

#include <groot.h>

namespace quill {

    class consts {
    public:
        static constexpr std::string_view   APP_DESCRIPTION     { "- bitpayments backend server." };

        static constexpr std::string_view   HTTP_INVOICE_PATH   { "/invoice" };

    };

}

#endif /* QUILL_QUILL_CONSTS_H */
