/**
 * @file constants.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef GROOT_CONSTANTS_H
#define GROOT_CONSTANTS_H

#include <cstdlib>
#include <string_view>

#include "main/groot_consts_gen.h"

namespace groot {

    class consts {
    public:
        static constexpr size_t             LOGGER_MAX_MESSAGE_LENGTH { 4096 };

        static constexpr std::string_view   SOURCE_DIR  { GR_SOURCE_DIR };

        static constexpr size_t             VERSION_MAJOR { GR_VERSION_MAJOR };
        static constexpr size_t             VERSION_MINOR { GR_VERSION_MINOR };
        static constexpr size_t             VERSION_PATCH { GR_VERSION_PATCH };
        static constexpr size_t             VERSION_BUILD { GR_VERSION_BUILD };
        static constexpr std::string_view   VERSION_FULL { GR_VERSION_FULL };

    };

}

#endif /* GROOT_CONSTANTS_H */
