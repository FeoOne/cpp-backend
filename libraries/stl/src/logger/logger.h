/**
 * @file logger.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef STL_LOGGER_H
#define STL_LOGGER_H

#include <cstdio>
#include <iostream>
#include <string_view>
#include <unordered_map>

#include "memory/memory.h"

#include "scalar/numeric.h"

namespace stl {

    class logger {
    public:
        STL_DECLARE_SMARTPOINTERS(logger)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(logger)

        enum class level_t {
            EMERG,
            ALERT,
            CRIT,
            ERROR,
            WARN,
            NOTICE,
            INFO,
            DEBUG
        };

        virtual ~logger() = default;

        virtual void log(level_t level,
                         const char *file,
                         size_t line,
                         const char *function,
                         const char *message,
                         ...) const noexcept = 0;

    protected:
        logger() = default;

    };

    class stdout_logger final : public logger {
    public:
        STL_DECLARE_SMARTPOINTERS(stdout_logger)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(stdout_logger)

        stdout_logger() = default;
        virtual ~stdout_logger() = default;

        void log(level_t level,
                 const char *file,
                 size_t line,
                 const char *function,
                 const char *message,
                 ...) const noexcept final;

    };

}

#endif /* STL_LOGGER_H */
