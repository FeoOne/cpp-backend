/**
 * @file hash.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include "crypto/hash.h"

namespace stl {

    // static
    u64 hash::quickhash64(const char *str, u64 mix) noexcept
    {
        static constexpr u64 MULP { 2654435789 };

        mix ^= 104395301;

        while(*str) {
            mix += (static_cast<u64>(*str) * MULP) ^ (mix >> 23);
            ++str;
        }

        return mix ^ (mix << 37);
    }

}
