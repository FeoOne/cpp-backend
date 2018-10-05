/**
 * @file application.cpp
 * @author Feo
 * @date 05/10/2018
 * @brief
 */

#include "parse/lexer.h"
#include "codegen/cpp/cpp_codegen.h"

#include "main/application.h"

application::application(int argc, char **argv) noexcept :
    _argument_parser { command_line_argument_parser::make_unique(argc, argv, "Prowler message generator.") }
{
}

int application::start() noexcept
{
    _argument_parser->parse();

    auto content { stl::filesystem::read_text_file(_argument_parser->input_file()) };

    auto lex { lexer::make_unique() };
    if (!lex->generate(content)) {
        return EXIT_FAILURE;
    }

    auto parser { parse_processor::make_unique() };
    if (!parser->parse(lex.get())) {
        return EXIT_FAILURE;
    }

    auto gen { cpp_codegen::make_unique() };
    auto output { gen->generate(parser.get()) };

    auto output_file_path { std::string { _argument_parser->output_dir() } + parser->contex().ns() + "_gen.h" };
    stl::filesystem::write_text_file(output_file_path, output);

    return EXIT_SUCCESS;
}

// static
int application::start(int argc, char **argv) noexcept
{
    stl::log_manager::setup();

    auto app { application::make_unique(argc, argv) };
    return app->start();
}
