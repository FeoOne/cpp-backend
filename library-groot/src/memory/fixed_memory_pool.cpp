//
// Created by Feo on 04/09/2018.
//

#include "memory/fixed_memory_pool.h"

namespace groot {

    fixed_memory_pool::fixed_memory_pool(size_t total_size) noexcept :
            _memory { nullptr },
            _allocated_chunks { nullptr },
            _free_chunks { nullptr },
            _total_size { static_cast<u32>(total_size) },
            _chunk_size { 0 }
    {
        _memory = new (std::nothrow) u8[_total_size]; // todo: aligned alloc

#ifdef GR_TRASHING_MEMORY_POOL
        std::memset(_memory, TRASH_ON_CREATE_SIGNATURE, _total_size);
#endif
    }

    // virtual
    fixed_memory_pool::~fixed_memory_pool()
    {
        delete[] _memory;
    }

    void *fixed_memory_pool::alloc(size_t alloc_size) noexcept
    {
        initialize_if_needed(static_cast<u32>(alloc_size));
        logassert(alloc_size + CHUNK_HEAD_SIZE == _chunk_size,
                "Can't alloc chunk which size is differs (initialized chunk size: %u, requested alloc size: %lu).",
                  _chunk_size - CHUNK_HEAD_SIZE,
                  alloc_size);

        u8 *memory { nullptr };

        if (alloc_size + CHUNK_HEAD_SIZE == _chunk_size) {
            auto chunk { _free_chunks };

            _free_chunks = chunk->next();
            if (_free_chunks != nullptr) {
                _free_chunks->prev(nullptr);
            }

            chunk->next(_allocated_chunks);
            if (_allocated_chunks != nullptr) {
                _allocated_chunks->prev(chunk);
            }
            _allocated_chunks = chunk;

            memory = reinterpret_cast<u8 *>(chunk) + CHUNK_HEAD_SIZE;

#ifdef GR_TRASHING_MEMORY_POOL
            std::memset(_memory, TRASH_ON_CREATE_SIGNATURE, alloc_size);
#endif
        }

        return memory;
    }

    void fixed_memory_pool::free(void *ptr) noexcept
    {
        logassert(ptr != nullptr, "Can't free nullptr.");
        logassert(_memory < ptr && ptr < _memory + _total_size, "Pointer didn't belong to pool.");
        if (ptr == nullptr || ptr <= _memory || ptr >= _memory + _total_size) {
            return;
        }

        auto chunk { reinterpret_cast<fixed_memory_chunk *>(static_cast<u8 *>(ptr) - CHUNK_HEAD_SIZE) };
        _allocated_chunks = chunk->next();
        if (_allocated_chunks != nullptr) {
            _allocated_chunks->prev(nullptr);
        }

        chunk->next(_free_chunks);
        if (_free_chunks != nullptr) {
            _free_chunks->prev(chunk);
        }

        _free_chunks = chunk;

#ifdef GR_TRASHING_MEMORY_POOL
        std::memset(ptr, TRASH_ON_FREE_SIGNATURE, _chunk_size - CHUNK_HEAD_SIZE);
#endif
    }

    void fixed_memory_pool::initialize_if_needed(u32 alloc_size) noexcept
    {
        if (_chunk_size == 0) {
            _chunk_size = static_cast<u32>(alloc_size + CHUNK_HEAD_SIZE);

            auto block_size { _chunk_size };
#ifdef GR_BOUNDING_MEMORY_POOL
            block_size += BOUNDS_CHECK_SIZE * 2;
#endif
            _chunk_count = _total_size / block_size;

            for (u32 i = 0; i < _chunk_count; ++i) {
                auto memory { _memory + i * block_size };

#ifdef GR_BOUNDING_MEMORY_POOL
                memory += BOUNDS_CHECK_SIZE;
#endif

                auto chunk { reinterpret_cast<fixed_memory_chunk *>(_memory) };
                chunk->prev(nullptr);
                chunk->next(_free_chunks);

                if (_free_chunks != nullptr) {
                    _free_chunks->prev(chunk);
                }

                _free_chunks = chunk;

#ifdef GR_BOUNDING_MEMORY_POOL
                std::memcpy(memory - BOUNDS_CHECK_SIZE, START_BOUND, BOUNDS_CHECK_SIZE);
                std::memcpy(memory + _chunk_size, END_BOUND, BOUNDS_CHECK_SIZE);
#endif

#ifdef GR_TRASHING_MEMORY_POOL
                std::memset(memory + CHUNK_HEAD_SIZE, TRASH_ON_ALLOCATE_SIGNATURE, alloc_size);
#endif
            }
        }
    }

}
