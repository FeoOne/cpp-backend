//
// Created by Feo on 03/09/2018.
//

#ifndef GROOT_DYNAMIC_MEMORY_POOL_H
#define GROOT_DYNAMIC_MEMORY_POOL_H

#include "scalar/numeric.h"
#include "memory/memory_pool.h"

namespace groot {

    /**
     *
     */
    class dynamic_memory_chunk final {
    public:
        GR_DECLARE_SMARTPOINTERS(dynamic_memory_chunk)
        GR_DELETE_ALL_DEFAULT(dynamic_memory_chunk)

        explicit dynamic_memory_chunk(size_t size) noexcept :
                _next { nullptr },
                _prev { nullptr },
                _size { static_cast<u32>(size) },
                _is_free { true }
        {}

        ~dynamic_memory_chunk() = default;

        void read(void *src) noexcept;
        void write(void *dst) noexcept;

        inline dynamic_memory_chunk *next() noexcept { return _next; }
        inline dynamic_memory_chunk *prev() noexcept { return _prev; }
        inline u32 size() const noexcept { return _size; }
        inline bool is_free() const noexcept { return _is_free; }

        inline void next(dynamic_memory_chunk *chunk) noexcept { _next = chunk; }
        inline void prev(dynamic_memory_chunk *chunk) noexcept { _prev = chunk; }
        inline void size(u32 s) noexcept { _size = s; }
        inline void set_free(bool f) noexcept { _is_free = f; }

    private:
        dynamic_memory_chunk *  _next;
        dynamic_memory_chunk *  _prev;
        u32                     _size;
        bool                    _is_free;

    };

    /**
     *
     */
    class dynamic_memory_pool final : public memory_pool {
    public:
        GR_DECLARE_SMARTPOINTERS(dynamic_memory_pool)
        GR_DELETE_ALL_DEFAULT(dynamic_memory_pool)

        explicit dynamic_memory_pool(size_t size, bool bounds_check) noexcept;
        virtual ~dynamic_memory_pool();

        void *alloc(size_t size) noexcept final;
        void free(void *ptr) noexcept final;

    private:
        static constexpr u32 CHUNK_SIZE { sizeof(dynamic_memory_chunk) };
        static constexpr u32 MIN_FREE_BLOCK_SIZE { 8 };

#ifdef GR_BOUNDING_MEMORY_POOL
        static constexpr u8 BOUNDS_CHECK_SIZE { 16 };

        static const u8 START_BOUND[BOUNDS_CHECK_SIZE];
        static const u8 END_BOUND[BOUNDS_CHECK_SIZE];
#endif

#ifdef GR_TRASHING_MEMORY_POOL
        static constexpr u8 TRASH_ON_CREATE_SIGNATURE { 0xCE };
        static constexpr u8 TRASH_ON_ALLOCATE_SIGNATURE { 0xAE };
        static constexpr u8 TRASH_ON_FREE_SIGNATURE { 0xFE };
#endif

        u8 *            _memory;

        u32             _total_size;
        u32             _free_size;

        bool            _check_bounds;

    };

}

#endif /* GROOT_DYNAMIC_MEMORY_POOL_H */
