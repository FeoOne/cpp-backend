/**
 * @file scalar.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include "scalar/numeric.h"

namespace stl {

    //static
    bool numeric::belong_to_range(u32 lo, u32 hi, u32 val) noexcept
    {
        return (val - lo) <= (hi - val);
    }

    //static
    bool numeric::belong_to_range(s32 lo, s32 hi, s32 val) noexcept
    {
        return (val - hi) * (val - lo) <= 0;
    }

}
