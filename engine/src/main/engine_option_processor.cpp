/**
 * @file engine_option_processor.cpp
 * @author Feo
 * @date 16/08/2018
 * @brief
 */

#include "main/engine_option_processor.h"

namespace engine {

    using namespace framework;

    engine_option_processor::engine_option_processor(int argc,
                                                     char **argv,
                                                     const std::string_view& app_description) noexcept :
            command_line_option_processor(argc, argv, app_description)
    {
        push_group("core", "Core options.", "Options related to core. This is detailed group description.");

        gchar *path { nullptr }; // @todo Check memory leak.
        add_option(command_line_option_type::STRING,
                   &path,
                   "config_path",
                   'c',
                   "Path to config.",
                   "PATH",
                   false,
                   false);
        _config_path = { path };
    }

    // virtual
//    engine_option_processor::~engine_option_processor()
//    {
//    }

}
