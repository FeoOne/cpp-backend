/**
 * @file string.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "scalar/string.h"

namespace groot {

    u64 quickhash64(const char *str, u64 mix)
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
