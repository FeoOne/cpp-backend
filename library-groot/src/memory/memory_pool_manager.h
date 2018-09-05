//
// Created by Feo on 05/09/2018.
//

#ifndef GROOT_MEMORY_POOL_MANAGER_H
#define GROOT_MEMORY_POOL_MANAGER_H

#include "memory/memory_pool.h"

namespace groot {

    /**
     *
     * @tparam T Memory pool type. Must inherit memory_pool.
     */
    template<typename T>
    class memory_pool_manager final {
    public:
        GR_DECLARE_SMARTPOINTERS(memory_pool_manager<T>)
        GR_DELETE_ALL_DEFAULT(memory_pool_manager)

        explicit memory_pool_manager(size_t pool_size) noexcept :
                _pools {},
                _pool_size { pool_size }
        {
            _pools.reserve(16);
        }

        ~memory_pool_manager() = default;

        void *alloc(size_t size) noexcept
        {
            logassert(0 < size && size < (_pool_size / 2), "Invalid alloc size.");

            index_type index { 0 };
            u8 *result { nullptr };
            auto required_size { size + INDEX_SIZE };

            // Try to find free space in already created pools
            for (auto i = 0; i < _pools.size(); ++i) {
                result = static_cast<u8 *>(_pools[i]->alloc(required_size));
                if (result != nullptr) {
                    index = static_cast<index_type>(i);
                    break;
                }
            }

            // If there is no free space, create new pool
            if (result == nullptr) {
                auto pool { std::make_unique<T>(_pool_size) };
                result = static_cast<u8 *>(pool->alloc(required_size));
                _pools.push_back(std::move(pool));

                index = static_cast<index_type>(_pools.size() - 1);
            }

            // Write pool's index to the chunk
            std::memcpy(result, &index, INDEX_SIZE);

            return result + INDEX_SIZE;
        }

        void free(void *ptr) noexcept
        {
            auto memory { static_cast<u8 *>(ptr) - INDEX_SIZE };
            auto index { *reinterpret_cast<index_type *>(memory) };

            logassert(0 <= index && index < _pools.size(), "Can't free chunk with %su pool's index.", index);

            if (0 <= index && index < _pools.size()) {
                _pools[index]->free(memory);
            }
        }

    private:
        using index_type = u16;

        static constexpr size_t INDEX_SIZE { sizeof(index_type) };

        std::vector<std::unique_ptr<T>>     _pools;
        size_t                              _pool_size;

    };

}

#endif /* GROOT_MEMORY_POOL_MANAGER_H */
