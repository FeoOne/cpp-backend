//
// Created by Feo on 03/09/2018.
//

#ifndef GROOT_DYNAMIC_MEMORY_POOL_H
#define GROOT_DYNAMIC_MEMORY_POOL_H

#include "memory/memory_pool.h"

namespace groot {

    /**
     *
     */
    class float_memory_chunk final {
    public:
        GR_DELETE_ALL_DEFAULT(float_memory_chunk)

        explicit float_memory_chunk(size_t size) noexcept :
                _next { nullptr },
                _prev { nullptr },
                _size { static_cast<u32>(size) },
                _is_free { true }
        {}

        ~float_memory_chunk() = default;

        void read(void *src) noexcept;
        void write(void *dst) noexcept;

        inline float_memory_chunk *prev() noexcept { return _prev; }
        inline void prev(float_memory_chunk *chunk) noexcept { _prev = chunk; }

        inline float_memory_chunk *next() noexcept { return _next; }
        inline void next(float_memory_chunk *chunk) noexcept { _next = chunk; }

        inline u32 size() const noexcept { return _size; }
        inline void size(u32 s) noexcept { _size = s; }

        inline bool is_free() const noexcept { return _is_free; }
        inline void set_free(bool f) noexcept { _is_free = f; }

    private:
        float_memory_chunk *    _next;
        float_memory_chunk *    _prev;
        u32                     _size;
        bool                    _is_free;

    };

    /**
     *
     */
    class float_memory_pool final : public memory_pool {
    public:
        GR_DECLARE_SMARTPOINTERS(float_memory_pool)
        GR_DELETE_ALL_DEFAULT(float_memory_pool)

        explicit float_memory_pool(size_t total_size) noexcept;
        virtual ~float_memory_pool();

        void *alloc(size_t alloc_size) noexcept final;
        void free(void *ptr) noexcept final;

    private:
        static constexpr u32 CHUNK_HEAD_SIZE { sizeof(float_memory_chunk) };
        static constexpr u32 MIN_FREE_BLOCK_SIZE { 16 };

        u8 *                _memory;

        u32                 _total_size;
        u32                 _free_size;

    };

}

#endif /* GROOT_DYNAMIC_MEMORY_POOL_H */
