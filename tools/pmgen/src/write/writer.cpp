/**
 * @file writer.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include <stl.h>

#include "parse/parse_contex.h"
#include "write/field_builder.h"
#include "write/header_builder.h"

#include "write/writer.h"

writer::writer()
{
}

writer::~writer()
{
}

void writer::write(const std::string& path, parse_processor& p) noexcept
{
    auto header { new header_builder };
    header->set_namespace(p.contex().ns());
    header->set_opcode_offset(p.contex().opcode_offset());

    u32 index { 0 };
    for (auto message: p.contex().messages()) {
        auto cls { new class_builder };
        cls->set_name(message->name());
        cls->set_opcode(p.contex().opcode_offset() + index);

        field_builder *prev_field_builder { nullptr };
        for (auto field: message->fields()) {
            auto property { new field_builder(prev_field_builder) };
            property->set_name(field->name());
            property->set_type(field->type());

            cls->add_field(property);
            prev_field_builder = property;
        }

        header->add_class(cls);

        ++index;
    }

    std::cout << header->build();
}
