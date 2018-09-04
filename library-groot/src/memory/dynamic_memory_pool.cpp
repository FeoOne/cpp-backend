//
// Created by Feo on 03/09/2018.
//

#include "logger/log_manager.h"

#include "memory/dynamic_memory_pool.h"

namespace groot {

#ifdef GR_BOUNDING_MEMORY_POOL
    // static
    const u8 dynamic_memory_pool::START_BOUND[BOUNDS_CHECK_SIZE]
            { '[', 'C', 'H', 'U', 'N', 'K', '.', '.', '.', '.', 'S', 'T', 'A', 'R', 'T', ']' };

    // static
    const u8 dynamic_memory_pool::END_BOUND[BOUNDS_CHECK_SIZE]
            { '[', 'C', 'H', 'U', 'N', 'K', '.', '.', '.', '.', '.', '.', 'E', 'N', 'D', ']' };
#endif

    void dynamic_memory_chunk::read(void *src) noexcept
    {
        std::memcpy(this, src, sizeof(dynamic_memory_chunk));
    }

    void dynamic_memory_chunk::write(void *dst) noexcept
    {
        std::memcpy(dst, this, sizeof(dynamic_memory_chunk));
    }

    dynamic_memory_pool::dynamic_memory_pool(size_t size, bool check_bounds) noexcept :
            _memory { nullptr },
            _total_size { 0 },
            _free_size { 0 },
            _check_bounds { check_bounds }
    {
        _total_size = static_cast<u32>(size);
        _free_size = static_cast<u32>(size - CHUNK_SIZE);

        _memory = new (std::nothrow) u8[size]; // @todo: aligned alloc

#ifdef GR_TRASHING_MEMORY_POOL
        std::memset(_memory, TRASH_ON_CREATE_SIGNATURE, size);
#endif

        // allocate first free block
#ifdef GR_BOUNDING_MEMORY_POOL
        _free_size -= BOUNDS_CHECK_SIZE * 2;

        dynamic_memory_chunk chunk { size - CHUNK_SIZE - BOUNDS_CHECK_SIZE * 2 };
        chunk.write(_memory + BOUNDS_CHECK_SIZE);

        std::memcpy(_memory, START_BOUND, BOUNDS_CHECK_SIZE);
        std::memcpy(_memory + size - BOUNDS_CHECK_SIZE, END_BOUND, BOUNDS_CHECK_SIZE);
#else
        dynamic_memory_chunk chunk { size - CHUNK_SIZE };
        chunk.write(_memory);
#endif
    }

    //virtual
    dynamic_memory_pool::~dynamic_memory_pool()
    {
        delete[] _memory;
    }

    void *dynamic_memory_pool::alloc(size_t size) noexcept
    {
        auto required_size { static_cast<u32>(size + CHUNK_SIZE) };
        auto memory { _memory };

#ifdef GR_BOUNDING_MEMORY_POOL
        required_size += BOUNDS_CHECK_SIZE * 2;
        memory = _memory + BOUNDS_CHECK_SIZE;
#endif

        // search for a chunk big enough
        auto chunk { reinterpret_cast<dynamic_memory_chunk *>(memory) };
        while (chunk != nullptr) {
            if (chunk->is_free() && chunk->size() >= required_size) {
                break;
            }
            chunk = chunk->next();
        }

        memory = reinterpret_cast<u8 *>(chunk);

        if (chunk != nullptr) {
            // if chunk is valid, create new free chunk with what remains of the chunk memory
            auto free_size { chunk->size() - required_size };
            if (free_size > MIN_FREE_BLOCK_SIZE) {
                dynamic_memory_chunk free_chunk { free_size };
                free_chunk.next(chunk->next());
                free_chunk.prev(chunk);
                free_chunk.write(memory + required_size);

                if (free_chunk.next() != nullptr) {
                    free_chunk.next()->prev(reinterpret_cast<dynamic_memory_chunk *>(memory + required_size));
                }

#ifdef GR_BOUNDING_MEMORY_POOL
                std::memcpy(memory + required_size - BOUNDS_CHECK_SIZE, START_BOUND, BOUNDS_CHECK_SIZE);
#endif

                chunk->next(reinterpret_cast<dynamic_memory_chunk *>(memory + required_size));
                chunk->size(static_cast<u32>(size));
            }

            // if chunk is found, update the pool size
            _free_size -= chunk->size();

            chunk->set_free(false);

#ifdef GR_BOUNDING_MEMORY_POOL
            std::memcpy(memory - BOUNDS_CHECK_SIZE, START_BOUND, BOUNDS_CHECK_SIZE);
            std::memcpy(memory + CHUNK_SIZE + chunk->size(), END_BOUND, BOUNDS_CHECK_SIZE);
#endif

#ifdef GR_TRASHING_MEMORY_POOL
            std::memset(memory + CHUNK_SIZE, TRASH_ON_ALLOCATE_SIGNATURE, chunk->size());
#endif

            memory += CHUNK_SIZE;
        }

        return memory;
    }

    void dynamic_memory_pool::free(void *ptr) noexcept
    {
        logassert(ptr != nullptr, "Can't free nullptr.");
        if (ptr == nullptr) {
            return;
        }

        auto chunk { reinterpret_cast<dynamic_memory_chunk *>(static_cast<u8 *>(ptr) - CHUNK_SIZE) };
        logassert(!chunk->is_free(), "Can't free already freed chunk.");
        if (chunk->is_free()) {
            return;
        }

        u32 full_size = chunk->size() + CHUNK_SIZE;
#ifdef GR_BOUNDING_MEMORY_POOL
        full_size += BOUNDS_CHECK_SIZE * 2;
#endif

        _free_size += chunk->size();

        auto head_chunk { chunk };
        auto prev_chunk { chunk->prev() };
        auto next_chunk { chunk->next() };

        // if chunk before is free then merge it with this one
        if (chunk->prev() != nullptr && chunk->prev()->is_free()) {
            head_chunk = chunk->prev();
            prev_chunk = chunk->prev()->prev();
            next_chunk = chunk->next();

            // include previous node in the chunk size so trash it as well
            full_size += chunk->prev()->size() + CHUNK_SIZE;
#ifdef GR_BOUNDING_MEMORY_POOL
            full_size += BOUNDS_CHECK_SIZE * 2;
#endif

            // if there is a next one, need to update its pointer
            if (chunk->next()) {
                chunk->next()->prev(head_chunk);

                if (chunk->next()->is_free()) {
                    // point to next's next
                    next_chunk = chunk->next()->next();

                    if (chunk->next()->next()) {
                        chunk->next()->next()->prev(head_chunk);
                    }

                    full_size += chunk->next()->size() + CHUNK_SIZE;
#ifdef GR_BOUNDING_MEMORY_POOL
                    full_size += BOUNDS_CHECK_SIZE * 2;
#endif
                }
            }
        } else if (chunk->next() && chunk->next()->is_free()) {
            // if next chunk is free lets merge it to the current one
            head_chunk = chunk;
            prev_chunk = chunk->prev();
            next_chunk = chunk->next()->next();

            // include the next node in the block size so trash it as well
            full_size += chunk->next()->size();
#ifdef GR_BOUNDING_MEMORY_POOL
            full_size += BOUNDS_CHECK_SIZE * 2;
#endif
        }

        auto memory { reinterpret_cast<u8 *>(head_chunk) };

#ifdef GR_TRASHING_MEMORY_POOL
        auto trash_memory { memory };
#ifdef GR_BOUNDING_MEMORY_POOL
        trash_memory -= BOUNDS_CHECK_SIZE;
#endif
        std::memset(trash_memory, TRASH_ON_FREE_SIGNATURE, full_size);
#endif

        auto free_size { full_size - CHUNK_SIZE };
#ifdef GR_BOUNDING_MEMORY_POOL
        free_size -= BOUNDS_CHECK_SIZE * 2;
#endif

        dynamic_memory_chunk free_chunk { free_size };
        free_chunk.prev(prev_chunk);
        free_chunk.next(next_chunk);
        free_chunk.write(memory);

#ifdef GR_BOUNDING_MEMORY_POOL
        std::memcpy(memory - BOUNDS_CHECK_SIZE, START_BOUND, BOUNDS_CHECK_SIZE);
        std::memcpy(memory + CHUNK_SIZE + free_size, END_BOUND, BOUNDS_CHECK_SIZE);
#endif
    }

}
