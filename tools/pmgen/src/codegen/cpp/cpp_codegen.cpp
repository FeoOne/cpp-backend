/**
 * @file cpp_codegen.cpp
 * @author Feo
 * @date 05/10/2018
 * @brief
 */

#include "codegen/cpp/field_builder.h"
#include "codegen/cpp/header_builder.h"

#include "codegen/cpp/cpp_codegen.h"

cpp_codegen::cpp_codegen()
{
}

std::string cpp_codegen::generate(parse_processor *parser) noexcept
{
    auto header { header_builder::make_unique() };
    header->set_namespace(parser->contex().ns());
    header->set_opcode_offset(parser->contex().opcode_offset());

    u32 index { 0 };
    for (auto message: parser->contex().messages()) {
        auto cls { class_builder::make_shared() };
        cls->set_name(message->name());
        cls->set_opcode(parser->contex().opcode_offset() + index);

        field_builder::sptr prev_field_builder { nullptr };
        for (auto field: message->fields()) {
            auto property { field_builder::make_shared(prev_field_builder) };
            property->set_name(field->name());
            property->set_type(field->type());

            cls->add_field(property);

            prev_field_builder = property;
        }

        header->add_class(cls);

        ++index;
    }

    header->set_message_count(index);

    return header->build();
}

