//
// Created by Feo on 04/09/2018.
//

#ifndef GROOT_STATIC_MEMORY_POOL_H
#define GROOT_STATIC_MEMORY_POOL_H

#include "scalar/numeric.h"
#include "memory/memory_pool.h"

namespace groot {

    /**
     * Memory chunk data struct.
     */
    class fixed_memory_chunk final {
    public:
        GR_DELETE_ALL_DEFAULT(fixed_memory_chunk)

        explicit fixed_memory_chunk(size_t size) noexcept :
        _next { nullptr },
        _prev { nullptr }
        {}

        ~fixed_memory_chunk() = default;

        inline fixed_memory_chunk *prev() noexcept { return _prev; }
        inline void prev(fixed_memory_chunk *chunk) noexcept { _prev = chunk; }

        inline fixed_memory_chunk *next() noexcept { return _next; }
        inline void next(fixed_memory_chunk *chunk) noexcept { _next = chunk; }

    private:
        fixed_memory_chunk *    _next;
        fixed_memory_chunk *    _prev;

    };

    /**
     * Static chunk size memory pool for same objects memory management.
     *
     * @brief Pool initializing lazily with first alloc call.
     *  This is due to the fact that some of stl containers used
     *  combined memory storage for both of contained object and
     *  control block. So there is no honest way to calculate combined
     *  memory storage before allocation.
     */
    class fixed_memory_pool final : public memory_pool {
    public:
        GR_DECLARE_SMARTPOINTERS(fixed_memory_pool)
        GR_DELETE_ALL_DEFAULT(fixed_memory_pool)

        explicit fixed_memory_pool(size_t total_size) noexcept;
        virtual ~fixed_memory_pool();

        void *alloc(size_t alloc_size) noexcept final;
        void free(void *ptr) noexcept final;

    private:
        static constexpr u32 CHUNK_HEAD_SIZE { sizeof(fixed_memory_chunk) };

        u8 *                    _memory;

        fixed_memory_chunk *    _allocated_chunks;
        fixed_memory_chunk *    _free_chunks;

        u32                     _total_size;
        u32                     _chunk_size;
        u32                     _chunk_count;

        /**
         * Lazy initialization.
         * @param alloc_size Chunk data size.
         */
        void initialize_if_needed(u32 alloc_size) noexcept;

    };

}

#endif /* GROOT_STATIC_MEMORY_POOL_H */
