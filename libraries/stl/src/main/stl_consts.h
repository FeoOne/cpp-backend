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
        static constexpr size_t logger_max_message_length { 4096 };

        static constexpr const char *source_dir { STL_SOURCE_DIR };

        struct version {
            static constexpr size_t major { STL_VERSION_MAJOR };
            static constexpr size_t minor { STL_VERSION_MINOR };
            static constexpr size_t patch { STL_VERSION_PATCH };
            static constexpr size_t build { STL_VERSION_BUILD };
            static constexpr const char *full { STL_VERSION_FULL };
        };

    };

}

#endif /* STL_CONSTANTS_H */
