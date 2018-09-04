//
// Created by Feo on 03/09/2018.
//

#ifndef GROOT_MEMORY_POOL_H
#define GROOT_MEMORY_POOL_H

#include "memory/memory.h"
#include "scalar/numeric.h"
#include "logger/log_manager.h"

#ifndef NDEBUG
#   define GR_TRASHING_MEMORY_POOL  1
#   define GR_BOUNDING_MEMORY_POOL  1
#endif

namespace groot {

    class memory_pool {
    public:
        GR_DECLARE_SMARTPOINTERS(memory_pool)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(memory_pool)

        virtual ~memory_pool() = default;

        virtual void *alloc(size_t size) noexcept = 0;
        virtual void free(void *ptr) noexcept = 0;

    protected:
#ifdef GR_TRASHING_MEMORY_POOL
        static constexpr u8 TRASH_ON_CREATE_SIGNATURE { 0xCE };
        static constexpr u8 TRASH_ON_ALLOCATE_SIGNATURE { 0xAE };
        static constexpr u8 TRASH_ON_FREE_SIGNATURE { 0xFE };
#endif

#ifdef GR_BOUNDING_MEMORY_POOL
        static constexpr u8 BOUNDS_CHECK_SIZE { 16 };
        static const u8 START_BOUND[BOUNDS_CHECK_SIZE];
        static const u8 END_BOUND[BOUNDS_CHECK_SIZE];
#endif

        memory_pool() = default;

    };

}

#endif /* GROOT_MEMORY_POOL_H */
