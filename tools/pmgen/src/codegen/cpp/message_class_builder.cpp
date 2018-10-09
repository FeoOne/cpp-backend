/**
 * @file message_class_builder.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include <stl.h>

#include "codegen/cpp/message_class_builder.h"

#define TPL_CLASSNAME       "%CLASSNAME%"
#define TPL_PUBLICSCOPE     "%PUBLICSCOPE%"
#define TPL_OPCODE          "%OPCODE%"

static const char *class_template {
    "\tclass " TPL_CLASSNAME " final : public pmp::message {\n"
    "\tpublic:\n"
    "\t\tSTL_DECLARE_SMARTPOINTERS(" TPL_CLASSNAME ")\n"
    "\t\tSTL_DELETE_ALL_DEFAULT(" TPL_CLASSNAME ")\n\n"
    "\t\tstatic constexpr u32 opcode { %OPCODE% };\n\n"
    "\t\texplicit " TPL_CLASSNAME "(const u8 *memory, size_t size) noexcept : pmp::message(memory, size) {}\n"
    "\t\tvirtual ~" TPL_CLASSNAME "() = default;\n\n"
    TPL_PUBLICSCOPE
    "\t};\n\n"
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

    std::string public_scope { "" };
    const field_presenter *previous_field { nullptr };
    for (const auto& field: _message->fields()) {
        auto builder { message_field_builder::make_unique(field, previous_field) };
        public_scope += builder->build();

        previous_field = field;
    }
    stl::string::replace(content, TPL_PUBLICSCOPE, public_scope);

    return content;
}
