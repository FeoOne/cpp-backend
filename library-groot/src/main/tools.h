/**
 * @file tools.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef GROOT_TOOLS_H
#define GROOT_TOOLS_H

#define GR_STR_IMPL(str)                #str
#define GR_STR(str)                     GR_STR_IMPL(str)

#define GR_COMMA()                      ,

#define GR_FORMAT_BOOL(b)               (b ? "true" : "false")

#define GR_UNIQUE_LOCK(n, m)            std::unique_lock<decltype(m)> n(m)

#define GR_NORETURN                     [[noreturn]]
#define GR_NODISCARD                    [[nodiscard]]
#define GR_UNUSED                       [[maybe_unused]]

#endif /* GROOT_TOOLS_H */
