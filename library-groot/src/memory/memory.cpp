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

namespace groot {

    // static
    size_t memory::page_size() noexcept
    {
        static auto size { static_cast<size_t>(sysconf(_SC_PAGE_SIZE)) };
        return size;
    }

    // static
    void *memory::_aligned_alloc(size_t size) noexcept
    {
#ifdef GR_PLATFORM_BSD
        return std::malloc(size);
#else
        return aligned_alloc(page_size(), size);
#endif
    }

}
