/**
 * @file engine_option_processor.cpp
 * @author Feo
 * @date 16/08/2018
 * @brief
 */

#include "main/rocket_option_processor.h"

namespace rocket {

    rocket_option_processor::rocket_option_processor(int argc,
                                                     char **argv,
                                                     const std::string_view& app_description) noexcept :
            command_line_option_processor(argc, argv, app_description),
            _config_path { nullptr }
    {
        push_group("core", "Core options.", "Options related to core. This is detailed group description.");

        add_option(groot::command_line_option_type::STRING,
                   &_config_path,
                   "config-path",
                   'c',
                   "Path to config.",
                   "PATH",
                   false,
                   false);
    }

    // virtual
//    rocket_option_processor::rocket_option_processor()
//    {
//    }

    std::string_view rocket_option_processor::config_path() const noexcept
    {
        return (_config_path != nullptr) ? _config_path : "";
    }

}
