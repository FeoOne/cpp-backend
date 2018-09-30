/**
 * @file platform.h
 * @author Feo
 * @date 30/08/2018
 * @brief
 */

#ifndef STL_PLATFORM_H
#define STL_PLATFORM_H

/*
 * Unix
 */
#if defined(__unix__) || defined(__unix)
#   define STL_PLATFORM_UNIX             1
#endif

/*
 * BSD
 */
#if __has_include(<sys/param.h>)
#   include <sys/param.h>
#   ifdef BSD
#       define STL_PLATFORM_BSD          1
#   endif
#endif

/*
 * Linux
 */
#ifdef __linux__
#   define STL_PLATFORM_LINUX            1
#endif

/*
 * Apple
 */
#if defined(__APPLE__) && defined(__MACH__)
#   define STL_PLATFORM_APPLE            1
#endif

/*
 * Windows
 */
#ifdef _WIN32
#   define STL_PLATFORM_WINDOWS          1
#endif

#endif /* STL_PLATFORM_H */
