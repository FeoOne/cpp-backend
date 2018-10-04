/**
 * @file header_builder.h
 * @author Feo
 * @date 03/10/2018
 * @brief
 */

#ifndef PMGEN_HEADER_BUILDER_H
#define PMGEN_HEADER_BUILDER_H

#include "write/class_builder.h"

class header_builder {
public:
    header_builder();
    ~header_builder() = default;

    void set_namespace(const std::string& name) noexcept;
    void set_opcode_offset(u32 offset) noexcept;

    void add_class(class_builder *cls) noexcept { _classes.push_back(cls); }

    const std::string& build() noexcept;

private:
    std::string                     _content;
    std::vector<class_builder *>    _classes;

};


#endif /* PMGEN_HEADER_BUILDER_H */
