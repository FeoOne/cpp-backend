//
// Created by Feo on 03/09/2018.
//

#ifndef STL_DYNAMIC_MEMORY_POOL_H
#define STL_DYNAMIC_MEMORY_POOL_H

#include <vector>

#include "memory/memory_pool_debug.h"

namespace stl {

    /**
     * Memory chunk data struct.
     */
    class float_memory_chunk final {
        STL_DELETE_ALL_DEFAULT(float_memory_chunk)

        friend class float_memory_page;

        float_memory_chunk *    _next;
        float_memory_chunk *    _prev;
        u32                     _size;
        bool                    _is_free;

        explicit float_memory_chunk(size_t size) noexcept :
                _next { nullptr },
                _prev { nullptr },
                _size { static_cast<u32>(size) },
                _is_free { true }
        {}

        ~float_memory_chunk() = default;

        inline float_memory_chunk *prev() noexcept { return _prev; }
        inline void prev(float_memory_chunk *chunk) noexcept { _prev = chunk; }

        inline float_memory_chunk *next() noexcept { return _next; }
        inline void next(float_memory_chunk *chunk) noexcept { _next = chunk; }

        inline u32 size() const noexcept { return _size; }
        inline void size(u32 s) noexcept { _size = s; }

        inline bool is_free() const noexcept { return _is_free; }
        inline void set_free(bool f) noexcept { _is_free = f; }

        static void write(float_memory_chunk *chunk, void *dst) noexcept;

    };

    /**
     * Memory page data struct.
     */
    class float_memory_page final {
        STL_DECLARE_SMARTPOINTERS(float_memory_page)
        STL_DELETE_ALL_DEFAULT(float_memory_page)

        friend class float_memory_pool;

        static constexpr u32 CHUNK_HEAD_SIZE { sizeof(float_memory_chunk) };
        static constexpr u32 MIN_FREE_BLOCK_SIZE { 16 };

        u8 *                _memory;

        u32                 _total_size;
        u32                 _free_size;

        explicit float_memory_page(u32 total_size) noexcept;
        virtual ~float_memory_page();

        void *alloc(u32 alloc_size) noexcept;
        void free(void *ptr) noexcept;

    };

    /**
     * Single threaded float size block memory pool.
     */
    class float_memory_pool final {
    public:
        STL_DECLARE_SMARTPOINTERS(float_memory_pool)
        STL_DELETE_ALL_DEFAULT(float_memory_pool)

        explicit float_memory_pool(size_t total_size) noexcept;
        ~float_memory_pool();

        void *alloc(size_t size) noexcept;
        void free(void *ptr) noexcept;

    private:
        using index_type = u16;

        static constexpr size_t INDEX_SIZE { sizeof(index_type) };

        std::vector<float_memory_page *>    _pages;

        u32                                 _total_size;

    };

}

#endif /* STL_DYNAMIC_MEMORY_POOL_H */
