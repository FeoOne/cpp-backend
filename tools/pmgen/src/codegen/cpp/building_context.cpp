/**
 * @file build_context.cpp
 * @author Feo
 * @date 08/10/2018
 * @brief
 */

#include "codegen/cpp/building_context.h"

building_context::building_context() :
        _opcode { 0 },
        _opcode_offset { 0 }
{
}

u32 building_context::acquire_opcode() noexcept
{
    u32 result { _opcode + _opcode_offset };
    ++_opcode;
    return result;
}
