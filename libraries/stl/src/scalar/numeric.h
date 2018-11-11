/**
 * @file scalar.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef STL_SCALAR_H
#define STL_SCALAR_H

#include <cstdlib>
#include <cstdint>

using s8 = int8_t;
using u8 = uint8_t;
using s16 = int16_t;
using u16 = uint16_t;
using s32 = int32_t;
using u32 = uint32_t;
using s64 = int64_t;
using u64 = uint64_t;

namespace stl {

    class numeric {
    public:
        static bool belong_to_range(u32 lo, u32 hi, u32 val) noexcept;
        static bool belong_to_range(s32 lo, s32 hi, s32 val) noexcept;

    };

}

#endif /* STL_SCALAR_H */
