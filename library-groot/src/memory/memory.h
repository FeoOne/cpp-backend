/**
 * @file memory.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef GROOT_MEMORY_H
#define GROOT_MEMORY_H

#define FW_DELETE_DEFAULT_CTOR(c)               c() = delete;
#define FW_DELETE_DEFAULT_COPY_CTOR(c)          c(const c&) = delete;
#define FW_DELETE_DEFAULT_MOVE_CTOR(c)          c(c&&) = delete;
#define FW_DELETE_DEFAULT_COPY_ASSIGN(c)        c& operator=(const c&) = delete;
#define FW_DELETE_DEFAULT_MOVE_ASSIGN(c)        c& operator=(c&&) = delete;

#define FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(c)    \
    FW_DELETE_DEFAULT_COPY_CTOR(c)              \
    FW_DELETE_DEFAULT_MOVE_CTOR(c)              \
    FW_DELETE_DEFAULT_COPY_ASSIGN(c)            \
    FW_DELETE_DEFAULT_MOVE_ASSIGN(c)

#define FW_DELETE_ALL_DEFAULT(c)                \
    FW_DELETE_DEFAULT_CTOR(c)                   \
    FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(c)

#define FW_DECLARE_SMARTPOINTERS(T)                                         \
    using sptr = std::shared_ptr<T>;                                        \
    using uptr = std::unique_ptr<T>;                                        \
    using wptr = std::weak_ptr<T>;                                          \
    template<typename... Args> static sptr make_shared(Args&&... args) {    \
        return std::make_shared<T>(std::forward<Args>(args)...);            \
    }                                                                       \
    template<typename... Args> static uptr make_unique(Args&&... args) {    \
        return std::make_unique<T>(std::forward<Args>(args)...);            \
    }

namespace groot {



}

#endif /* GROOT_MEMORY_H */
