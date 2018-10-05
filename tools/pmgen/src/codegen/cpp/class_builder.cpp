/**
 * @file class_builder.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include <stl.h>

#include "codegen/cpp/class_builder.h"

#define TPL_CLASSNAME       "%CLASSNAME%"
#define TPL_PUBLICSCOPE     "%PUBLICSCOPE%"
#define TPL_PRIVATESCOPE    "%PRIVATESCOPE%"
#define TPL_OPCODE          "%OPCODE%"

static const char *class_template {
    "\tclass " TPL_CLASSNAME " : public pmp::message {\n"
    "\tpublic:\n"
    "\t\tstatic constexpr u32 opcode { %OPCODE% };\n\n"
    TPL_PUBLICSCOPE
    "\t};\n\n"
};

class_builder::class_builder() :
        _content { class_template }
{
}

void class_builder::set_name(const std::string& name) noexcept
{
    stl::string::replace(_content, TPL_CLASSNAME, name);
}

void class_builder::set_opcode(u32 opcode) noexcept
{
    stl::string::replace(_content, TPL_OPCODE, std::to_string(opcode));
}

const std::string& class_builder::build() noexcept
{
    std::string public_scope { "" };
    for (auto field: _fields) {
        public_scope += field->build();
    }
    stl::string::replace(_content, TPL_PUBLICSCOPE, public_scope);

    return _content;
}
