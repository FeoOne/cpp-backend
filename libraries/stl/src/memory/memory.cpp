/**
 * @file memory.cpp
 * @author Feo
 * @date 12/09/2018
 * @brief
 */

#include <unistd.h>
#include <stdlib.h>

#include <jemalloc/jemalloc.h>

#include "main/platform.h"
#include "logger/log_manager.h"

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
        return std::malloc(size);
    }

    // static
    void *memory::realloc_impl(void *memory, size_t size) noexcept
    {
        return std::realloc(memory, size);
    }

    // static
    void *memory::aligned_alloc_impl(size_t size) noexcept
    {
#ifdef STL_PLATFORM_APPLE
        return std::malloc(size);
#else
        return std::aligned_alloc(page_size(), size);
#endif
    }

    // static
    void memory::print_stats() noexcept
    {
        malloc_stats_print(nullptr, nullptr, nullptr);
    }

}
