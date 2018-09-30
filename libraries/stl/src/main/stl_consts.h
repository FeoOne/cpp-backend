/**
 * @file constants.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef STL_CONSTANTS_H
#define STL_CONSTANTS_H

#include <cstdlib>
#include <string_view>

#include "main/stl_consts_gen.h"

namespace stl {

    class consts {
    public:
        static constexpr size_t             LOGGER_MAX_MESSAGE_LENGTH { 4096 };

        static constexpr std::string_view   SOURCE_DIR  { STL_SOURCE_DIR };

        static constexpr size_t             VERSION_MAJOR { STL_VERSION_MAJOR };
        static constexpr size_t             VERSION_MINOR { STL_VERSION_MINOR };
        static constexpr size_t             VERSION_PATCH { STL_VERSION_PATCH };
        static constexpr size_t             VERSION_BUILD { STL_VERSION_BUILD };
        static constexpr std::string_view   VERSION_FULL { STL_VERSION_FULL };

    };

}

#endif /* STL_CONSTANTS_H */
