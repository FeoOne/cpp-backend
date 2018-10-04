/**
 * @file command_line_argument_parser.cpp
 * @author Feo
 * @date 05/10/2018
 * @brief
 */

#include "main/command_line_argument_parser.h"

command_line_argument_parser::command_line_argument_parser(int argc,
                                                           char **argv,
                                                           const std::string_view& app_description) noexcept :
        stl::command_line_argument_parser(argc, argv, app_description),
        _input { nullptr },
        _output { nullptr }
{
    push_group("main", "Main options.", "This is detailed group description.");

    add_option(stl::command_line_option_type::STRING,
               &_input,
               "input",
               'i',
               "File with message schema.",
               "PATH",
               false,
               false);
    add_option(stl::command_line_option_type::STRING,
               &_output,
               "output",
               'o',
               "File to output generated code.",
               "PATH",
               false,
               false);
}

