/**
 * @file hash.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef STL_HASH_H
#define STL_HASH_H

#include "scalar/numeric.h"

namespace stl {

    class hash {
    public:
        static u64 quickhash64(const char *str, u64 mix = 0) noexcept;

    };

}

#endif /* STL_HASH_H */
