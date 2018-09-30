/**
 * @file log_manager.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef GROOT_LOG_MANAGER_H
#define GROOT_LOG_MANAGER_H

#include "main/tools.h"
#include "memory/memory.h"

#include "logger/logger.h"



#ifdef NDEBUG
#define logassert(cond, format, ...)
#define logdebug(format, ...)
#else
#define logassert(cond, format, ...)                                                                \
    do { if (!(cond)) { logdebug("Assertion failed '" GR_STR(cond) "'. " format, ##__VA_ARGS__); } } while (false)
#define logdebug(format, ...)                                                       \
    groot::log_manager::get_logger()->log(groot::logger::level_t::DEBUG,            \
                                          __FILE__,                                 \
                                          __LINE__,                                 \
                                          __FUNCTION__,                             \
                                          format,                                   \
                                          ##__VA_ARGS__)
#endif

#define loginfo(format, ...)                                                        \
    groot::log_manager::get_logger()->log(groot::logger::level_t::INFO,             \
                                          __FILE__,                                 \
                                          __LINE__,                                 \
                                          __FUNCTION__,                             \
                                          format,                                   \
                                          ##__VA_ARGS__)

#define lognotice(format, ...)                                                      \
    groot::log_manager::get_logger()->log(groot::logger::level_t::NOTICE,           \
                                          __FILE__,                                 \
                                          __LINE__,                                 \
                                          __FUNCTION__,                             \
                                          format,                                   \
                                          ##__VA_ARGS__)

#define logwarn(format, ...)                                                        \
    groot::log_manager::get_logger()->log(groot::logger::level_t::WARN,             \
                                          __FILE__,                                 \
                                          __LINE__,                                 \
                                          __FUNCTION__,                             \
                                          format,                                   \
                                          ##__VA_ARGS__)

#define logerror(format, ...)                                                       \
    groot::log_manager::get_logger()->log(groot::logger::level_t::ERROR,            \
                                          __FILE__,                                 \
                                          __LINE__,                                 \
                                          __FUNCTION__,                             \
                                          format,                                   \
                                          ##__VA_ARGS__)

#define logcrit(format, ...)            \
    do { groot::log_manager::get_logger()->log(groot::logger::level_t::CRIT,        \
                                               __FILE__,                            \
                                               __LINE__,                            \
                                               __FUNCTION__,                        \
                                               format,                              \
                                               ##__VA_ARGS__);                      \
        abort(); } while (false)

#define logalert(format, ...)                                                       \
    do { groot::log_manager::get_logger()->log(groot::logger::level_t::ALERT,       \
                                               __FILE__,                            \
                                               __LINE__,                            \
                                               __FUNCTION__,                        \
                                               format,                              \
                                               ##__VA_ARGS__);                      \
        abort(); } while (false)

#define logemerg(format, ...)                                                       \
    do { groot::log_manager::get_logger()->log(groot::logger::level_t::EMERG,       \
                                               __FILE__,                            \
                                               __LINE__,                            \
                                               __FUNCTION__,                        \
                                               format,                              \
                                               ##__VA_ARGS__);                      \
        abort(); } while (false)

namespace groot {

    class log_manager final {
    public:
        GR_DELETE_ALL_DEFAULT(log_manager)

        static void setup() noexcept;

        static const logger::uptr& get_logger() noexcept { return _logger; }

    private:
        static logger::uptr     _logger;

    };

}

#endif /* GROOT_LOG_MANAGER_H */
