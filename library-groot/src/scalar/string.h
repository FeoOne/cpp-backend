/**
 * @file string.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef GROOT_STRING_H
#define GROOT_STRING_H

#include <string>
#include <string_view>

#include "scalar/numeric.h"

namespace groot {

    u64 quickhash64(const char *str, u64 mix = 0);

}

#endif /* GROOT_STRING_H */
