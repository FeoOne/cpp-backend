//
// Created by Feo on 04/09/2018.
//

#include <inttypes.h>

#include "memory/fixed_memory_pool.h"

#define GR_PAGE_RESERVE_COUNT   16 // @todo: move to config

namespace groot {

    fixed_memory_page::fixed_memory_page(u32 data_size, u32 total_size) noexcept :
            _memory { nullptr },
            _allocated_chunks { nullptr },
            _free_chunks { nullptr },
            _data_size { data_size },
            _total_size { total_size },
            _chunk_size { 0 },
            _chunk_count { 0 }
    {
        _memory = memory::aligned_alloc<u8>(_total_size);

#ifdef GR_TRASHING_MEMORY_POOL
        std::memset(_memory,
                memory_pool_debug::TRASH_ON_CREATE_SIGNATURE,
                _total_size);
#endif

        _chunk_size = _data_size + CHUNK_HEAD_SIZE;

        auto block_size { _chunk_size };
#ifdef GR_BOUNDING_MEMORY_POOL
        block_size += memory_pool_debug::BOUNDS_CHECK_SIZE * 2;
#endif
        _chunk_count = _total_size / block_size;

        for (u32 i = 0; i < _chunk_count; ++i) {
            auto memory { _memory + i * block_size };

#ifdef GR_BOUNDING_MEMORY_POOL
            memory += memory_pool_debug::BOUNDS_CHECK_SIZE;
#endif

            auto chunk { reinterpret_cast<fixed_memory_chunk *>(_memory) };
            chunk->prev(nullptr);
            chunk->next(_free_chunks);

            if (_free_chunks != nullptr) {
                _free_chunks->prev(chunk);
            }

            _free_chunks = chunk;

#ifdef GR_BOUNDING_MEMORY_POOL
            std::memcpy(memory - memory_pool_debug::BOUNDS_CHECK_SIZE,
                    memory_pool_debug::START_BOUND,
                    memory_pool_debug::BOUNDS_CHECK_SIZE);
            std::memcpy(memory + _chunk_size,
                    memory_pool_debug::END_BOUND,
                    memory_pool_debug::BOUNDS_CHECK_SIZE);
#endif

#ifdef GR_TRASHING_MEMORY_POOL
            std::memset(memory + CHUNK_HEAD_SIZE,
                    memory_pool_debug::TRASH_ON_ALLOCATE_SIGNATURE,
                    _data_size);
#endif
        }
    }

    // virtual
    fixed_memory_page::~fixed_memory_page()
    {
        delete[] _memory;
    }

    void *fixed_memory_page::alloc() noexcept
    {
        u8 *memory { nullptr };

        if (_data_size + CHUNK_HEAD_SIZE == _chunk_size) {
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
            std::memset(_memory,
                    memory_pool_debug::TRASH_ON_CREATE_SIGNATURE,
                    _data_size);
#endif
        }

        return memory;
    }

    void fixed_memory_page::free(void *ptr) noexcept
    {
        if (ptr == nullptr) {
            logwarn("Can't free nullptr.");
            return;
        }

        if (ptr <= _memory || ptr >= _memory + _total_size) {
            logwarn("Pointer 0x%" PRIXPTR " didn't bound to pool memory space (0x% " PRIXPTR " - 0x%" PRIXPTR ").",
                    ptr,
                    _memory,
                    _memory + _total_size);
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
        std::memset(ptr,
                memory_pool_debug::TRASH_ON_FREE_SIGNATURE,
                _chunk_size - CHUNK_HEAD_SIZE);
#endif
    }

    fixed_memory_pool::fixed_memory_pool(size_t data_size, size_t page_size) noexcept :
            _pages {},
            _block_size { static_cast<u32>(data_size) + INDEX_SIZE },
            _page_size { static_cast<u32>(page_size) }
    {
        _pages.reserve(GR_PAGE_RESERVE_COUNT);
    }

    fixed_memory_pool::~fixed_memory_pool()
    {
        for (auto page: _pages) {
            delete page;
        }
    }

    void *fixed_memory_pool::alloc() noexcept
    {
        index_type index { 0 };
        u8 *result { nullptr };

        // Try to find free space in already created pools
        for (size_t i = 0; i < _pages.size(); ++i) {
            result = static_cast<u8 *>(_pages[i]->alloc());
            if (result != nullptr) {
                index = static_cast<index_type>(i);
                break;
            }
        }

        // If there is no free space, create new pool
        if (result == nullptr) {
            auto page { _pages.emplace_back(new (std::nothrow) fixed_memory_page(_block_size, _page_size)) };
            result = static_cast<u8 *>(page->alloc());
            index = static_cast<index_type>(_pages.size() - 1);

            lognotice("Created memory page with index %su.", index);
        }

        // Write pool's index to the chunk
        std::memcpy(result, &index, INDEX_SIZE);

        return result + INDEX_SIZE;
    }

    void fixed_memory_pool::free(void *ptr) noexcept
    {
        auto memory { static_cast<u8 *>(ptr) - INDEX_SIZE };
        auto index { *reinterpret_cast<index_type *>(memory) };

        if (index >= _pages.size()) {
            logwarn("Can't free chunk with %su page's index. Total page count: %lu.", index, _pages.size());
            return;
        }

        _pages[index]->free(memory);
    }

}
