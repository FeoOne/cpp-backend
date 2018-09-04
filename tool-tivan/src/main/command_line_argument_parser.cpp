/**
 * @file command_line_argument_parser.cpp
 * @author Feo
 * @date 02/09/2018
 * @brief
 */

#include "main/command_line_argument_parser.h"

namespace tivan {

    command_line_argument_parser::command_line_argument_parser(int argc,
                                                               char **argv,
                                                               const std::string_view& app_description) noexcept :
            groot::command_line_argument_parser(argc, argv, app_description),
            _input_file { nullptr },
            _output_file { nullptr }
    {
        push_group("tivan", "Tivan options.", "Message generator options.");

        add_option(groot::command_line_option_type::FILENAME,
                   &_input_file,
                   "input-file",
                   'i',
                   "Path to schema.",
                   "PATH",
                   false,
                   false);

        add_option(groot::command_line_option_type::FILENAME,
                   &_output_file,
                   "output-file",
                   'o',
                   "Path to generated source code.",
                   "PATH",
                   false,
                   false);
    }

    std::string_view command_line_argument_parser::input_file() const noexcept
    {
        return (_input_file != nullptr) ? _input_file : "";
    }

    std::string_view command_line_argument_parser::output_file() const noexcept
    {
        return (_output_file != nullptr) ? _output_file : "";
    }

}
