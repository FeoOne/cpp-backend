/**
 * @file header_builder.cpp
 * @author Feo
 * @date 03/10/2018
 * @brief
 */

#include <stl.h>

#include "write/header_builder.h"

#define TPL_HEADERGUARD     "%HEADERGUARD%"
#define TPL_NAMESPACE       "%NAMESPACE%"
#define TPL_BODY            "%BODY%"
#define TPL_OPCODEOFFSET    "%OPCODEOFFSET%"

static const char *header_template {
    "// This code is auto-generated. Do not modify.\n\n"
    "#ifndef " TPL_HEADERGUARD "\n"
    "#define " TPL_HEADERGUARD "\n\n"
    "#include <pmp.h>\n\n"
    "namespace pmp::" TPL_NAMESPACE " {\n\n"
    TPL_BODY
    "\tinline size_t opcode_to_index(u32 opcode) noexcept { return opcode - %OPCODEOFFSET%; }\n\n"
    "}\n\n"
    "#endif /* " TPL_HEADERGUARD " */\n"
};

header_builder::header_builder() :
        _content { header_template }
{
}

void header_builder::set_namespace(const std::string& name) noexcept
{
    // namespace
    stl::string::replace(_content, TPL_NAMESPACE, name);

    // header guard
    auto guard { name };
    stl::string::make_uppercase(guard);
    guard = "PMP_" + guard + "_H";
    stl::string::replace_all(_content, TPL_HEADERGUARD, guard);
}

void header_builder::set_opcode_offset(u32 offset) noexcept
{
    stl::string::replace(_content, TPL_OPCODEOFFSET, std::to_string(offset));
}

const std::string& header_builder::build() noexcept
{
    std::string body { "" };
    for (auto cls: _classes) {
        body += cls->build();
    }
    stl::string::replace(_content, TPL_BODY, body);

    return _content;
}
