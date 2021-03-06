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

#define STL_IS_STR_EQUAL(str1, str2)     (std::strcmp(str1, str2) == 0)

#define STL_COMMA()                      ,

#define STL_FORMAT_BOOL(b)               (b ? "true" : "false")

#define STL_CALL_ONCE(fn) \
        do { static std::once_flag once_flag; std::call_once(once_flag, fn); } while (false)

#define STL_UNIQUE_LOCK(n, m)            std::unique_lock<decltype(m)> n(m)

#define STL_NORETURN                     [[noreturn]]
#define STL_NODISCARD                    [[nodiscard]]
#define STL_UNUSED                       [[maybe_unused]]

#define STL_SAFE_ERASE(c, k)            \
    do {                                \
        const auto& it { c.find(k) };   \
            if (it != c.end()) {        \
                c.erase(it);            \
            }                           \
    } while (false)

#endif /* STL_TOOLS_H */
