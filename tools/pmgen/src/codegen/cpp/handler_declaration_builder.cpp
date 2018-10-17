/**
 * @file handler_builder.cpp
 * @author Feo
 * @date 07/10/2018
 * @brief
 */

#include "codegen/cpp/handler_declaration_builder.h"

#define TPL_NAMESPACE       "%NAMESPACE%"
#define TPL_HEADERGUARD     "%HEADERGUARD%"
#define TPL_METHODS         "%METHODS%"
#define TPL_MESSAGENAME     "%MESSAGENAME%"
#define TPL_SWITCH          "%SWITCH%"
#define TPL_OPCODEOFFSET    "%OPCODEOFFSET%"
#define TPL_OPCODECOUNT     "%OPCODECOUNT%"

static const char *header_template {
    "// This code is auto-generated. Do not modify.\n\n"
    "#ifndef " TPL_HEADERGUARD "\n"
    "#define " TPL_HEADERGUARD "\n\n"
    "#include <pmp.h>\n\n"
    "namespace pmp::" TPL_NAMESPACE " {\n\n"
    "\tclass message_handler : public basic_message_handler {\n"
    "\tpublic:\n"
    "\t\tvirtual ~message_handler() = default;\n\n"
    "\t\tbool handle_message(u32 opcode, const u8 *memory, size_t size) noexcept final {\n"
    "\t\t\tauto result { true };\n"
    "\t\t\tswitch (opcode) {\n"
    TPL_SWITCH
    "\t\t\t\tdefault: result = false; break;\n"
    "\t\t\t}\n"
    "\t\t\treturn result;\n"
    "\t\t}\n\n"
//    "\t\tstatic bool own_opcode(u32 opcode) noexcept { return opcode - " TPL_OPCODEOFFSET " < " TPL_OPCODECOUNT "; }\n\n"
    "\tprotected:\n"
    "\t\tmessage_handler() = default;\n\n"
    TPL_METHODS "\n"
    "\t};\n\n"
    "}\n\n"
    "#endif /* " TPL_HEADERGUARD " */\n"
};

static const char *handler_method_template {
    "\t\tvirtual void handle_" TPL_MESSAGENAME "(pmp::" TPL_NAMESPACE "::" TPL_MESSAGENAME "::uptr&& message) noexcept = 0;\n"
};

static const char *handler_switch_template {
    "\t\t\t\tcase (" TPL_MESSAGENAME "::opcode): {\n"
    "\t\t\t\t\thandle_" TPL_MESSAGENAME "(" TPL_MESSAGENAME "::make_unique(memory, size));\n"
    "\t\t\t\t\tbreak;\n"
    "\t\t\t\t}\n"
};

handler_declaration_builder::handler_declaration_builder(building_context *build_context,
                                                         const parsing_context *parse_context) noexcept :
        _build_context { build_context },
        _parse_context { parse_context }
{

}

// virtual
std::string handler_declaration_builder::build() const noexcept
{
    std::string content { header_template };

    auto guard { "PMP_" + stl::string::to_uppercase(_parse_context->ns()) + "_HANDLER_H" };
    stl::string::replace_all(content, TPL_HEADERGUARD, guard);

    std::string methods;
    std::string switches;
    for (auto message: _parse_context->messages()) {
        methods += std::string { handler_method_template };
        stl::string::replace_all(methods, TPL_MESSAGENAME, message->name());
        stl::string::replace_all(methods, TPL_NAMESPACE, _parse_context->ns());

        switches += std::string { handler_switch_template };
        stl::string::replace_all(switches, TPL_MESSAGENAME, message->name());
    }

    stl::string::replace_all(content, TPL_NAMESPACE, _parse_context->ns());
    stl::string::replace_all(content, TPL_METHODS, methods);
    stl::string::replace_all(content, TPL_SWITCH, switches);

    stl::string::replace(content, TPL_OPCODEOFFSET, std::to_string(_parse_context->opcode_offset()));
    stl::string::replace(content, TPL_OPCODECOUNT, std::to_string(_build_context->opcode_count()));

    return content;
}
