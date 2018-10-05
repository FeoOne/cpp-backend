/**
 * @file class_builder.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMGEN_CLASS_BUILDER_H
#define PMGEN_CLASS_BUILDER_H

#include "codegen/cpp/field_builder.h"

class class_builder {
public:
    STL_DECLARE_SMARTPOINTERS(class_builder)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(class_builder)

    class_builder();
    ~class_builder() = default;

    void set_name(const std::string& name) noexcept;
    void set_opcode(u32 opcode) noexcept;

    const std::string& build() noexcept;

    void add_field(const field_builder::sptr& field) noexcept { _fields.push_back(field); }

private:
    std::string                         _content;
    std::vector<field_builder::sptr>    _fields;

};

#endif /* PMGEN_CLASS_BUILDER_H */
