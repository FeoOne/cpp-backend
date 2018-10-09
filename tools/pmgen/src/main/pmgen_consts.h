/**
 * @file pmgen_consts.h
 * @author Feo
 * @date 07/10/2018
 * @brief
 */

#ifndef PMGEN_PMGEN_CONSTS_H
#define PMGEN_PMGEN_CONSTS_H

#include <stl.h>

class consts {
public:
    STL_DELETE_ALL_DEFAULT(consts)

    static constexpr std::string_view GENERATED_HEADER_SUFFIX { "_gen.h" };

};

#endif /* PMGEN_PMGEN_CONSTS_H */
