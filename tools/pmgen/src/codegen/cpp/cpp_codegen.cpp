/**
 * @file cpp_codegen.cpp
 * @author Feo
 * @date 05/10/2018
 * @brief
 */

#include "main/pmgen_consts.h"
#include "codegen/cpp/building_context.h"
#include "codegen/cpp/message_declaration_builder.h"
#include "codegen/cpp/handler_declaration_builder.h"

#include "codegen/cpp/cpp_codegen.h"

std::map<std::string, std::string> cpp_codegen::generate(parse_processor *parser) noexcept
{
    static const std::string header_suffix { consts::generated_header_suffix };

    std::map<std::string, std::string> result {};

    auto parse_context { parser->contex() };
    auto build_context { building_context::make_unique() };
    build_context->opcode_offset(parse_context->opcode_offset());

    {
        // message declaration
        auto builder { message_declaration_builder::make_unique(build_context.get(), parse_context) };
        result.emplace(std::make_pair(parser->contex()->ns() + "_message" + header_suffix, builder->build()));
    }

    {
        // message handler declaration and definition
        auto builder { handler_declaration_builder::make_unique(build_context.get(), parse_context) };
        result.emplace(std::make_pair(parser->contex()->ns() + "_handler" + header_suffix, builder->build()));
    }

    return result;
}
