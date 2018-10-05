/**
 * @file header_builder.h
 * @author Feo
 * @date 03/10/2018
 * @brief
 */

#ifndef PMGEN_HEADER_BUILDER_H
#define PMGEN_HEADER_BUILDER_H

#include "codegen/cpp/class_builder.h"

class header_builder {
public:
    STL_DECLARE_SMARTPOINTERS(header_builder)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(header_builder)

    header_builder();
    ~header_builder() = default;

    void set_namespace(const std::string& name) noexcept;
    void set_opcode_offset(u32 offset) noexcept;
    void set_message_count(size_t count) noexcept;

    void add_class(const class_builder::sptr& cls) noexcept { _classes.push_back(cls); }

    const std::string& build() noexcept;

private:
    std::string                         _content;
    std::vector<class_builder::sptr>    _classes;

};

#endif /* PMGEN_HEADER_BUILDER_H */
