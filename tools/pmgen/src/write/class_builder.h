/**
 * @file class_builder.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMGEN_CLASS_BUILDER_H
#define PMGEN_CLASS_BUILDER_H

#include <string>

#include "message/message_class.h"
#include "write/field_builder.h"

class class_builder {
public:
    class_builder();
    ~class_builder() = default;

    void set_name(const std::string& name) noexcept;

    const std::string& build() noexcept;

    void add_field(field_builder *field) noexcept { _fields.push_back(field); }

private:
    std::string                     _content;
    std::vector<field_builder *>    _fields;

};

#endif /* PMGEN_CLASS_BUILDER_H */
