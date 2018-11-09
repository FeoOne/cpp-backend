/**
 * @file memory.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef STL_MEMORY_H
#define STL_MEMORY_H

#include <atomic>
#include <memory>

#include <jemalloc/jemalloc.h>

#define STL_DELETE_DEFAULT_CTOR(c)               c() = delete;
#define STL_DELETE_DEFAULT_COPY_CTOR(c)          c(const c&) = delete;
#define STL_DELETE_DEFAULT_MOVE_CTOR(c)          c(c&&) = delete;
#define STL_DELETE_DEFAULT_COPY_ASSIGN(c)        c& operator=(const c&) = delete;
#define STL_DELETE_DEFAULT_MOVE_ASSIGN(c)        c& operator=(c&&) = delete;

#define STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(c)    \
    STL_DELETE_DEFAULT_COPY_CTOR(c)              \
    STL_DELETE_DEFAULT_MOVE_CTOR(c)              \
    STL_DELETE_DEFAULT_COPY_ASSIGN(c)            \
    STL_DELETE_DEFAULT_MOVE_ASSIGN(c)

#define STL_DELETE_ALL_DEFAULT(c)                \
    STL_DELETE_DEFAULT_CTOR(c)                   \
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(c)

#define STL_DECLARE_SMARTPOINTERS(T)                                                    \
    using sptr = std::shared_ptr<T>;                                                    \
    using uptr = std::unique_ptr<T>;                                                    \
    using wptr = std::weak_ptr<T>;                                                      \
    template<typename... StlArgs> static sptr make_shared(StlArgs&&... args) noexcept { \
        return std::make_shared<T>(std::forward<StlArgs>(args)...);                     \
    }                                                                                   \
    template<typename... StlArgs> static uptr make_unique(StlArgs&&... args) noexcept { \
        return std::make_unique<T>(std::forward<StlArgs>(args)...);                     \
    }

#define STL_DECLARE_NEW_DELETE(base_type)                                                           \
    template<typename T, typename... Args>                                                          \
    static T *create(Args&&... args) noexcept {                                                     \
        return new (stl::memory::aligned_alloc<void>(sizeof(T))) T(std::forward<Args>(args)...);    \
    }                                                                                               \
    static void destroy(base_type *obj) noexcept {                                                  \
        obj->~base_type();                                                                          \
        stl::memory::free(obj);                                                                     \
    }

namespace stl {

    class memory final {
    public:
        static size_t page_size() noexcept;

        template<typename T>
        static inline T *malloc(size_t size) noexcept {
            return reinterpret_cast<T *>(malloc_impl(size));
        }

        template<typename T>
        static inline T *realloc(void *memory, size_t size) noexcept {
            return reinterpret_cast<T *>(realloc_impl(memory, size));
        }

        template<typename T>
        static inline T *aligned_alloc(size_t size) noexcept {
            return reinterpret_cast<T *>(aligned_alloc_impl(size));
        }


        static void free(void *mem) noexcept;

    private:
        static void *malloc_impl(size_t size) noexcept;
        static void *realloc_impl(void *memory, size_t size) noexcept;
        static void *aligned_alloc_impl(size_t size) noexcept;

    };

}

#endif /* STL_MEMORY_H */
