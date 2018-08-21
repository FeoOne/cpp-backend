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

        static constexpr std::string_view   SOURCE_DIR  { FW_SOURCE_DIR };

        static constexpr size_t             VERSION_MAJOR { FW_VERSION_MAJOR };
        static constexpr size_t             VERSION_MINOR { FW_VERSION_MINOR };
        static constexpr size_t             VERSION_MAINTENANCE { FW_VERSION_MAINTENANCE };
        static constexpr size_t             VERSION_BUILD { FW_VERSION_BUILD };
        static constexpr std::string_view   VERSION_FULL { FW_VERSION_FULL };

    };

}

#endif /* GROOT_CONSTANTS_H */
