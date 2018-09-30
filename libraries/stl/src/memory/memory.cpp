/**
 * @file memory.cpp
 * @author Feo
 * @date 12/09/2018
 * @brief
 */

#include <unistd.h>
#include <stdlib.h>

#include "main/platform.h"

#include "memory/memory.h"

namespace stl {

    // static
    size_t memory::page_size() noexcept
    {
        static auto size { static_cast<size_t>(sysconf(_SC_PAGE_SIZE)) };
        return size;
    }

    // static
    void *memory::malloc_impl(size_t size) noexcept
    {
        return je_malloc(size);
    }

    // static
    void *memory::aligned_alloc_impl(size_t size) noexcept
    {
        return je_aligned_alloc(page_size(), size);
    }

    // static
    void memory::free(void *mem) noexcept {
        je_free(mem);
    }

}
