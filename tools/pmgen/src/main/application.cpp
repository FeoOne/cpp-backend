/**
 * @file application.cpp
 * @author Feo
 * @date 05/10/2018
 * @brief
 */

#include "parse/lexer.h"

#include "main/application.h"

application::application(int argc, char **argv) noexcept :
    _argument_parser { command_line_argument_parser::make_unique(argc, argv, "Prowler message generator.") }
{
}

application::~application()
{
}

int application::start() noexcept
{
    _argument_parser->parse();

    auto content { stl::filesystem::read_whole_file(_argument_parser->input_file()) };

    auto lex { lexer::make_unique() };
    if (!lex->generate(content)) {
        return EXIT_FAILURE;
    }

    auto parser { parse_processor::make_unique() };
    parser->parse(lex.get());

    writer w;
    w.write("../../../message/", p);

    return EXIT_SUCCESS;
}

// static
int application::start(int argc, char **argv) noexcept
{
    auto app { application::make_unique(argc, argv, description) };
    return app->start();
}
