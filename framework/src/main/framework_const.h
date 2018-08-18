/**
 * @file constants.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef FRAMEWORK_CONSTANTS_H
#define FRAMEWORK_CONSTANTS_H

#include <cstdlib>
#include <string_view>

#include "main/framework_const_gen.h"

namespace framework {

    class framework_const {
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

#endif /* FRAMEWORK_CONSTANTS_H */
