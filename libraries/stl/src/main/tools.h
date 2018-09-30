/**
 * @file tools.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef STL_TOOLS_H
#define STL_TOOLS_H

#define STL_STR_IMPL(str)                #str
#define STL_STR(str)                     STL_STR_IMPL(str)

#define STL_COMMA()                      ,

#define STL_FORMAT_BOOL(b)               (b ? "true" : "false")

#define STL_UNIQUE_LOCK(n, m)            std::unique_lock<decltype(m)> n(m)

#define STL_NORETURN                     [[noreturn]]
#define STL_NODISCARD                    [[nodiscard]]
#define STL_UNUSED                       [[maybe_unused]]

#endif /* STL_TOOLS_H */
