/**
 * @file build_context.h
 * @author Feo
 * @date 08/10/2018
 * @brief
 */

#ifndef PMGEN_BUILD_CONTEXT_H
#define PMGEN_BUILD_CONTEXT_H

#include <stl.h>

class building_context {
public:
    STL_DECLARE_SMARTPOINTERS(building_context)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(building_context)

    building_context();
    virtual ~building_context() = default;

    void opcode_offset(u32 offset) noexcept { _opcode_offset = offset; }
    u32 opcode_offset() const noexcept { return _opcode_offset; }
    u32 opcode_count() const noexcept { return _opcode; }

    u32 acquire_opcode() noexcept;

private:
    u32         _opcode;
    u32         _opcode_offset;

};

#endif /* PMGEN_BUILD_CONTEXT_H */
