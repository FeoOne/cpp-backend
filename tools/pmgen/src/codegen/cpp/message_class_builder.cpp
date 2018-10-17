/**
 * @file message_class_builder.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include <stl.h>

#include "codegen/cpp/message_class_builder.h"

#define TPL_OPCODE          "%OPCODE%"
#define TPL_CLASSNAME       "%CLASSNAME%"
#define TPL_MESSAGEFIELDS   "%MESSAGEFIELDS%"
#define TPL_BUILDERFIELDS   "%BUILDERFIELDS%"
#define TPL_FIELDNAME       "%FIELDNAME%"
#define TPL_CALCSIZE        "%CALCSIZE%"
#define TPL_COPYMEMORY      "%COPYMEMORY%"

static const char *class_template {
    // message
    "\tclass " TPL_CLASSNAME " final : public pmp::message {\n"
    "\tpublic:\n"
    "\t\tSTL_DECLARE_SMARTPOINTERS(" TPL_CLASSNAME ")\n"
    "\t\tSTL_DELETE_ALL_DEFAULT(" TPL_CLASSNAME ")\n\n"
    "\t\tstatic constexpr u32 opcode { " TPL_OPCODE " };\n\n"
    "\t\texplicit " TPL_CLASSNAME "(const u8 *memory, size_t size) noexcept : pmp::message(memory, size) {}\n"
    "\t\tvirtual ~" TPL_CLASSNAME "() = default;\n\n"
    TPL_MESSAGEFIELDS
    "\t};\n\n"
    // message builder
    "\tclass " TPL_CLASSNAME "_builder final : public pmp::message_builder {\n"
    "\tpublic:\n"
    "\t\tSTL_DECLARE_SMARTPOINTERS(" TPL_CLASSNAME "_builder)\n"
    "\t\tSTL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(" TPL_CLASSNAME "_builder)\n\n"
    "\t\t" TPL_CLASSNAME "_builder() = default;\n"
    "\t\tvirtual ~" TPL_CLASSNAME "_builder() = default;\n\n"
    TPL_BUILDERFIELDS
    "\t\tvoid build(u8 **memptr, size_t *length) const noexcept final {\n"
    "\t\t\tsize_t counter { 0 };\n"
    TPL_CALCSIZE
    "\t\t\t*length = counter;\n"
    "\t\t\tauto memory { stl::memory::aligned_alloc<u8>(counter) };\n"
    "\t\t\tcounter = 0;\n"
    TPL_COPYMEMORY
    "\t\t\t*memptr = memory;\n"
    "\t\t}\n"
    "\t};\n\n"
};

static const char *size_template {
    "\t\t\tcounter += " TPL_FIELDNAME "_length();\n"
};

static const char *copy_template {
    "\t\t\tcopy(&memory[counter], _" TPL_FIELDNAME ");\n"
    "\t\t\tcounter += " TPL_FIELDNAME "_length();\n"
};
static const char *copy_array_template {
        "\t\t\tcopy(&memory[counter], _" TPL_FIELDNAME ", _" TPL_FIELDNAME "_count);\n"
        "\t\t\tcounter += " TPL_FIELDNAME "_length();\n"
};

message_class_builder::message_class_builder(building_context *build_context,
                                             const message_presenter *message) noexcept :
        _build_context { build_context },
        _message { message }
{
}

// virtual
std::string message_class_builder::build() const noexcept
{
    std::string content { class_template };

    stl::string::replace_all(content, TPL_CLASSNAME, _message->name());
    stl::string::replace(content, TPL_OPCODE, std::to_string(_build_context->acquire_opcode()));

    std::string message_fields;
    std::string builder_fields;
    std::string size_calculate;
    std::string copy_memory;

    const field_presenter *previous_field { nullptr };

    for (const auto& field: _message->fields()) {
        {
            auto builder { message_field_builder::make_unique(field, previous_field) };
            message_fields += builder->build();
        }

        {
            auto builder { message_builder_field_builder::make_unique(field) };
            builder_fields += builder->build();

            size_calculate += std::string { size_template };
            stl::string::replace(size_calculate, TPL_FIELDNAME, field->name());

            if (field->is_array()) {
                copy_memory += std::string{copy_array_template};
            } else {
                copy_memory += std::string{copy_template};
            }
            stl::string::replace_all(copy_memory, TPL_FIELDNAME, field->name());
        }

        previous_field = field;
    }
    stl::string::replace(content, TPL_MESSAGEFIELDS, message_fields);
    stl::string::replace(content, TPL_BUILDERFIELDS, builder_fields);
    stl::string::replace(content, TPL_CALCSIZE, size_calculate);
    stl::string::replace(content, TPL_COPYMEMORY, copy_memory);

    return content;
}
