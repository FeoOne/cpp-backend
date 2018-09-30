/**
 * @file engine_option_processor.cpp
 * @author Feo
 * @date 16/08/2018
 * @brief
 */

#include "main/command_line_argument_parser.h"

namespace engine {

    command_line_argument_parser::command_line_argument_parser(int argc,
                                                               char **argv,
                                                               const std::string_view& app_description) noexcept :
            stl::command_line_argument_parser(argc, argv, app_description),
            _config_path { nullptr }
    {
        push_group("core", "Core options.", "Options related to core. This is detailed group description.");

        add_option(stl::command_line_option_type::STRING,
                   &_config_path,
                   "config",
                   'c',
                   "Path to config.",
                   "PATH",
                   false,
                   false);
    }

    // virtual
//    engine_option_processor::engine_option_processor()
//    {
//    }

    std::string_view command_line_argument_parser::config_path() const noexcept
    {
        return (_config_path != nullptr) ? _config_path : "";
    }

}
