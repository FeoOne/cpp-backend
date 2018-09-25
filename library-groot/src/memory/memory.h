/**
 * @file memory.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef GROOT_MEMORY_H
#define GROOT_MEMORY_H

#include <atomic>
#include <memory>

#include <jemalloc/jemalloc.h>

#define GR_DELETE_DEFAULT_CTOR(c)               c() = delete;
#define GR_DELETE_DEFAULT_COPY_CTOR(c)          c(const c&) = delete;
#define GR_DELETE_DEFAULT_MOVE_CTOR(c)          c(c&&) = delete;
#define GR_DELETE_DEFAULT_COPY_ASSIGN(c)        c& operator=(const c&) = delete;
#define GR_DELETE_DEFAULT_MOVE_ASSIGN(c)        c& operator=(c&&) = delete;

#define GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(c)    \
    GR_DELETE_DEFAULT_COPY_CTOR(c)              \
    GR_DELETE_DEFAULT_MOVE_CTOR(c)              \
    GR_DELETE_DEFAULT_COPY_ASSIGN(c)            \
    GR_DELETE_DEFAULT_MOVE_ASSIGN(c)

#define GR_DELETE_ALL_DEFAULT(c)                \
    GR_DELETE_DEFAULT_CTOR(c)                   \
    GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(c)

#define GR_DECLARE_SMARTPOINTERS(T)                                                 \
    using sptr = std::shared_ptr<T>;                                                \
    using uptr = std::unique_ptr<T>;                                                \
    using wptr = std::weak_ptr<T>;                                                  \
    template<typename... Args> static sptr make_shared(Args&&... args) noexcept {   \
        return std::make_shared<T>(std::forward<Args>(args)...);                    \
    }                                                                               \
    template<typename... Args> static uptr make_unique(Args&&... args) noexcept {   \
        return std::make_unique<T>(std::forward<Args>(args)...);                    \
    }

namespace groot {

    class memory final {
    public:
        static size_t page_size() noexcept;

        template<typename T>
        static T *aligned_alloc(size_t size) noexcept {
            return static_cast<T *>(aligned_alloc_impl(size));
        }

    private:
        static void *aligned_alloc_impl(size_t size) noexcept;

    };

}

#endif /* GROOT_MEMORY_H */
