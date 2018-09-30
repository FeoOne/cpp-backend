/**
 * @file string.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef STL_STRING_H
#define STL_STRING_H

#include <string>
#include <string_view>

#include "scalar/numeric.h"

namespace stl {

    u64 quickhash64(const char *str, u64 mix = 0);

}

#endif /* STL_STRING_H */
