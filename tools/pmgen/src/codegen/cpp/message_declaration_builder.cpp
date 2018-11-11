/**
 * @file message_declaration_builder.cpp
 * @author Feo
 * @date 03/10/2018
 * @brief
 */

#include <stl.h>

#include "codegen/cpp/message_class_builder.h"

#include "codegen/cpp/message_declaration_builder.h"

#define TPL_HEADERGUARD     "%HEADERGUARD%"
#define TPL_NAMESPACE       "%NAMESPACE%"
#define TPL_BODY            "%BODY%"

static const char *header_template {
    "// This code is auto-generated. Do not modify.\n\n"
    "#ifndef " TPL_HEADERGUARD "\n"
    "#define " TPL_HEADERGUARD "\n\n"
    "#include <pmp.h>\n\n"
    "namespace pmp::" TPL_NAMESPACE " {\n\n"
    TPL_BODY
    "}\n\n"
    "#endif /* " TPL_HEADERGUARD " */\n"
};

message_declaration_builder::message_declaration_builder(building_context *build_context,
                                                         const parsing_context *parse_context) noexcept :
        _build_context { build_context },
        _parse_context { parse_context }
{
}

// virtual
std::string message_declaration_builder::build() const noexcept
{
    std::string content { header_template };

    // namespace
    stl::string::replace(content, TPL_NAMESPACE, _parse_context->ns());

    // header guard
    auto guard { "PMP_" + stl::string::to_uppercase(_parse_context->ns()) + "_H" };
    stl::string::replace_all(content, TPL_HEADERGUARD, guard);

    // message declaration
    std::string body;
    for (auto message: _parse_context->messages()) {
        auto builder { message_class_builder::make_unique(_build_context, message) };
        body += builder->build();
    }
    stl::string::replace(content, TPL_BODY, body);

    return content;
}
