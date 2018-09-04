//
// Created by Feo on 04/09/2018.
//

#include "memory/memory_pool.h"

namespace groot {

#ifdef GR_BOUNDING_MEMORY_POOL
    // static
    const u8 memory_pool::START_BOUND[BOUNDS_CHECK_SIZE]
            { '[', 'C', 'H', 'U', 'N', 'K', '.', '.', '.', '.', 'S', 'T', 'A', 'R', 'T', ']' };

    // static
    const u8 memory_pool::END_BOUND[BOUNDS_CHECK_SIZE]
            { '[', 'C', 'H', 'U', 'N', 'K', '.', '.', '.', '.', '.', '.', 'E', 'N', 'D', ']' };
#endif

}
