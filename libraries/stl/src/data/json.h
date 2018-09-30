/**
 * @file json.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef STL_JSON_H
#define STL_JSON_H

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include "data/nlohmann-json.h"

#pragma clang diagnostic pop

namespace stl {

    using json = nlohmann::json;

}

#endif /* STL_JSON_H */
