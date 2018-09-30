//
// Created by Feo on 04/09/2018.
//

#ifndef STL_FIXED_MEMORY_POOL_H
#define STL_FIXED_MEMORY_POOL_H

#include <vector>

#include "scalar/numeric.h"
#include "memory/memory_pool_debug.h"

namespace stl {

    /**
     * Memory chunk data struct.
     */
    class fixed_memory_chunk final {
        STL_DELETE_ALL_DEFAULT(fixed_memory_chunk)

        friend class fixed_memory_page;

        fixed_memory_chunk *    _next;
        fixed_memory_chunk *    _prev;

        explicit fixed_memory_chunk(size_t size) noexcept :
                _next { nullptr },
                _prev { nullptr }
        {}

        ~fixed_memory_chunk() = default;

        inline fixed_memory_chunk *prev() noexcept { return _prev; }
        inline void prev(fixed_memory_chunk *chunk) noexcept { _prev = chunk; }

        inline fixed_memory_chunk *next() noexcept { return _next; }
        inline void next(fixed_memory_chunk *chunk) noexcept { _next = chunk; }

    };

    /**
     * Memory page data struct.
     */
    class fixed_memory_page final {
        STL_DECLARE_SMARTPOINTERS(fixed_memory_page)
        STL_DELETE_ALL_DEFAULT(fixed_memory_page)

        friend class fixed_memory_pool;

        static constexpr u32 CHUNK_HEAD_SIZE { sizeof(fixed_memory_chunk) };

        u8 *                    _memory;

        fixed_memory_chunk *    _allocated_chunks;
        fixed_memory_chunk *    _free_chunks;

        u32                     _data_size;
        u32                     _total_size;
        u32                     _chunk_size;
        u32                     _chunk_count;

        explicit fixed_memory_page(u32 data_size, u32 total_size) noexcept;
        virtual ~fixed_memory_page();

        void *alloc() noexcept;
        void free(void *ptr) noexcept;

    };

    /**
     * Single threaded fixed size block memory pool.
     */
    class fixed_memory_pool final {
    public:
        STL_DECLARE_SMARTPOINTERS(fixed_memory_pool)
        STL_DELETE_ALL_DEFAULT(fixed_memory_pool)

        explicit fixed_memory_pool(size_t data_size, size_t page_size) noexcept;
        ~fixed_memory_pool();

        void *alloc() noexcept;
        void free(void *ptr) noexcept;

    private:
        using index_type = u16;

        static constexpr u32 INDEX_SIZE { sizeof(index_type) };

        std::vector<fixed_memory_page *>    _pages;

        u32                                 _block_size;
        u32                                 _page_size;

    };

}

#endif /* STL_FIXED_MEMORY_POOL_H */
