/**
 * @file logger.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef FRAMEWORK_LOGGER_H
#define FRAMEWORK_LOGGER_H

#include <cstdio>
#include <iostream>
#include <string_view>
#include <unordered_map>

#include "memory/memory.h"

#include "scalar/scalar.h"

namespace framework {

    class logger {
    public:
        FW_DECLARE_SMARTPOINTERS(logger)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(logger)

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
        FW_DECLARE_SMARTPOINTERS(stdout_logger)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(stdout_logger)

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

#endif /* FRAMEWORK_LOGGER_H */
