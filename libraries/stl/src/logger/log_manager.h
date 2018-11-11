/**
 * @file log_manager.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef STL_LOG_MANAGER_H
#define STL_LOG_MANAGER_H

#include "main/tools.h"
#include "memory/memory.h"

#include "logger/logger.h"



#ifdef NDEBUG
#define logassert(cond, format, ...)
#define logdebug(format, ...)
#else
#define logassert(cond, format, ...) \
    do { if (!(cond)) { logdebug("Assertion failed '" STL_STR(cond) "'. " format, ##__VA_ARGS__); } } while (false)
#define logdebug(format, ...)                                                   \
    stl::log_manager::get_logger()->log(stl::logger::level_t::DEBUG,            \
                                        __FILE__,                               \
                                        __LINE__,                               \
                                        __FUNCTION__,                           \
                                        format,                                 \
                                        ##__VA_ARGS__)
#endif

#define loginfo(format, ...)                                                    \
    stl::log_manager::get_logger()->log(stl::logger::level_t::INFO,             \
                                        __FILE__,                               \
                                        __LINE__,                               \
                                        __FUNCTION__,                           \
                                        format,                                 \
                                        ##__VA_ARGS__)

#define lognotice(format, ...)                                                      \
    stl::log_manager::get_logger()->log(stl::logger::level_t::NOTICE,           \
                                          __FILE__,                                 \
                                          __LINE__,                                 \
                                          __FUNCTION__,                             \
                                          format,                                   \
                                          ##__VA_ARGS__)

#define logwarn(format, ...)                                                        \
    stl::log_manager::get_logger()->log(stl::logger::level_t::WARN,             \
                                          __FILE__,                                 \
                                          __LINE__,                                 \
                                          __FUNCTION__,                             \
                                          format,                                   \
                                          ##__VA_ARGS__)

#define logerror(format, ...)                                                       \
    stl::log_manager::get_logger()->log(stl::logger::level_t::ERROR,            \
                                          __FILE__,                                 \
                                          __LINE__,                                 \
                                          __FUNCTION__,                             \
                                          format,                                   \
                                          ##__VA_ARGS__)

#define logcrit(format, ...)            \
    do { stl::log_manager::get_logger()->log(stl::logger::level_t::CRIT,        \
                                               __FILE__,                            \
                                               __LINE__,                            \
                                               __FUNCTION__,                        \
                                               format,                              \
                                               ##__VA_ARGS__);                      \
        abort(); } while (false)

#define logalert(format, ...)                                                       \
    do { stl::log_manager::get_logger()->log(stl::logger::level_t::ALERT,       \
                                               __FILE__,                            \
                                               __LINE__,                            \
                                               __FUNCTION__,                        \
                                               format,                              \
                                               ##__VA_ARGS__);                      \
        abort(); } while (false)

#define logemerg(format, ...)                                                       \
    do { stl::log_manager::get_logger()->log(stl::logger::level_t::EMERG,       \
                                               __FILE__,                            \
                                               __LINE__,                            \
                                               __FUNCTION__,                        \
                                               format,                              \
                                               ##__VA_ARGS__);                      \
        abort(); } while (false)

namespace stl {

    class log_manager final {
    public:
        STL_DELETE_ALL_DEFAULT(log_manager)

        static void setup() noexcept;

        static const logger::uptr& get_logger() noexcept { return _logger; }

    private:
        static logger::uptr     _logger;

    };

}

#endif /* STL_LOG_MANAGER_H */
