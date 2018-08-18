/**
 * @file log_manager.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef FRAMEWORK_LOG_MANAGER_H
#define FRAMEWORK_LOG_MANAGER_H

#include "main/tools.h"
#include "memory/memory.h"

#include "logger/logger.h"

#define logassert(cond) \
    do { if (!(cond)) { logdebug("Assertion failed '" FW_STR(cond) "'."); abort(); } } while (false)
#define logcond(cond, format, ...) \
    do { if ((cond)) { logwarn("Check condition: '" FW_STR(cond) "'. " format, ##__VA_ARGS__); } } while (false)

#define logdebug(format, ...)           framework::log_manager::logger()->log(framework::logger::level_t::DEBUG,   \
                                                                              __FILE__,                            \
                                                                              __LINE__,                            \
                                                                              __FUNCTION__,                        \
                                                                              format,                              \
                                                                              ##__VA_ARGS__)
#define loginfo(format, ...)            framework::log_manager::logger()->log(framework::logger::level_t::INFO,    \
                                                                              __FILE__,                            \
                                                                              __LINE__,                            \
                                                                              __FUNCTION__,                        \
                                                                              format,                              \
                                                                              ##__VA_ARGS__)
#define lognotice(format, ...)          framework::log_manager::logger()->log(framework::logger::level_t::NOTICE,  \
                                                                              __FILE__,                            \
                                                                              __LINE__,                            \
                                                                              __FUNCTION__,                        \
                                                                              format,                              \
                                                                              ##__VA_ARGS__)
#define logwarn(format, ...)            framework::log_manager::logger()->log(framework::logger::level_t::WARN,    \
                                                                              __FILE__,                            \
                                                                              __LINE__,                            \
                                                                              __FUNCTION__,                        \
                                                                              format,                              \
                                                                              ##__VA_ARGS__)
#define logerror(format, ...)           framework::log_manager::logger()->log(framework::logger::level_t::ERROR,   \
                                                                              __FILE__,                            \
                                                                              __LINE__,                            \
                                                                              __FUNCTION__,                        \
                                                                              format,                              \
                                                                              ##__VA_ARGS__)
#define logcrit(format, ...)            \
    do { framework::log_manager::logger()->log(framework::logger::level_t::CRIT,    \
                                               __FILE__,                            \
                                               __LINE__,                            \
                                               __FUNCTION__,                        \
                                               format,                              \
                                               ##__VA_ARGS__);                      \
        abort(); } while (false)
#define logalert(format, ...)                                                       \
    do { framework::log_manager::logger()->log(framework::logger::level_t::ALERT,   \
                                               __FILE__,                            \
                                               __LINE__,                            \
                                               __FUNCTION__,                        \
                                               format,                              \
                                               ##__VA_ARGS__);                      \
        abort(); } while (false)
#define logemerg(format, ...)                                                       \
    do { framework::log_manager::logger()->log(framework::logger::level_t::EMERG,   \
                                               __FILE__,                            \
                                               __LINE__,                            \
                                               __FUNCTION__,                        \
                                               format,                              \
                                               ##__VA_ARGS__);                      \
        abort(); } while (false)

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

#endif /* FRAMEWORK_LOG_MANAGER_H */
