/**
 * @file log_manager.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef FRAMEWORK_LOG_MANAGER_H
#define FRAMEWORK_LOG_MANAGER_H

#include "logger/logger.h"

#define logdebug(format, ...)           log_manager::logger()->log(logger::level_t::DEBUG,      \
                                                                   __FILE__,                    \
                                                                   __LINE__,                    \
                                                                   __FUNCTION__,                \
                                                                   format,                      \
                                                                   ##__VA_ARGS__)
#define loginfo(format, ...)            log_manager::logger()->log(logger::level_t::INFO,       \
                                                                   __FILE__,                    \
                                                                   __LINE__,                    \
                                                                   __FUNCTION__,                \
                                                                   format,                      \
                                                                   ##__VA_ARGS__)
#define lognotice(format, ...)          log_manager::logger()->log(logger::level_t::NOTICE,     \
                                                                   __FILE__,                    \
                                                                   __LINE__,                    \
                                                                   __FUNCTION__,                \
                                                                   format,                      \
                                                                   ##__VA_ARGS__)
#define logwarn(format, ...)            log_manager::logger()->log(logger::level_t::WARN,       \
                                                                   __FILE__,                    \
                                                                   __LINE__,                    \
                                                                   __FUNCTION__,                \
                                                                   format,                      \
                                                                   ##__VA_ARGS__)
#define logerror(format, ...)           log_manager::logger()->log(logger::level_t::ERROR,      \
                                                                   __FILE__,                    \
                                                                   __LINE__,                    \
                                                                   __FUNCTION__,                \
                                                                   format,                      \
                                                                   ##__VA_ARGS__)
#define logcrit(format, ...)            log_manager::logger()->log(logger::level_t::CRIT,       \
                                                                   __FILE__,                    \
                                                                   __LINE__,                    \
                                                                   __FUNCTION__,                \
                                                                   format,                      \
                                                                   ##__VA_ARGS__)
#define logalert(format, ...)           log_manager::logger()->log(logger::level_t::ALERT,      \
                                                                   __FILE__,                    \
                                                                   __LINE__,                    \
                                                                   __FUNCTION__,                \
                                                                   format,                      \
                                                                   ##__VA_ARGS__)
#define logemerg(format, ...)           log_manager::logger()->log(logger::level_t::EMERG,      \
                                                                   __FILE__,                    \
                                                                   __LINE__,                    \
                                                                   __FUNCTION__,                \
                                                                   format,                      \
                                                                   ##__VA_ARGS__)

namespace framework {

    class log_manager final {
    public:
        FW_DELETE_ALL_DEFAULT(log_manager)

        static void setup() noexcept;

        static const logger::uptr& logger() noexcept { return _logger; }

    private:
        static logger::uptr     _logger;

    };

}

#endif /* PROJECT_LOG_MANAGER_H */
