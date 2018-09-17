//
// Created by Feo on 13/09/2018.
//

#ifndef GROOT_LOCKFREE_MEMORY_POOL_H
#define GROOT_LOCKFREE_MEMORY_POOL_H

#include <thread>
#include <atomic>
#include <unordered_map>

#include "scalar/numeric.h"

namespace groot {

    class anchor {
    public:
        u16             available;
        u16             count;
        u8              state;
        u8              tag[3];
    };

    class active {
    public:
        u32             ptr;
        u32             credits;
    };

    class sizeclass {
    public:
        u32             size;
        u32             superblock_size;
    };

    class descriptor;

    class procheap {
    public:
        active          active;
        descriptor *    partial;
    };

    class descriptor {
    public:
        anchor          anchor;
        descriptor *    next;
        void *          superblock;
    };

    class lockfree_memory_heap {
    public:

    private:

    };

    class lockfree_memory_pool {
    public:

    private:
        static std::unordered_map<std::thread::id, lockfree_memory_heap *>  _local_heap;

        static lockfree_memory_heap *heap() noexcept;

    };

}

#endif /* GROOT_LOCKFREE_MEMORY_POOL_H */
