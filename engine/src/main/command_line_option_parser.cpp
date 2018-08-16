//
// Created by Feo on 16/08/2018.
//

#include "main/command_line_option_parser.h"

namespace engine {

    command_line_option_parser::command_line_option_parser(int argc, char **argv) noexcept :
            _argc { argc },
            _argv { argv },
            _context { nullptr },
            _options {}
    {

    }

    void command_line_option_parser::add_option(const std::string_view& long_name,
                                                char short_name,
                                                option_var_type type,
                                                void *pointer,
                                                const std::string_view& decription,
                                                const std::string_view& argument_decription) noexcept
    {

    }

    void command_line_option_parser::parse(const std::string_view& app_description) noexcept
    {
        GError *error { nullptr };

        _options.push_back({ nullptr, 0, 0, G_OPTION_ARG_NONE, nullptr, nullptr, nullptr });

        _context = g_option_context_new(app_description.data());
        g_option_context_add_main_entries(_context, _options.data(), nullptr);
        if (!g_option_context_parse(_context, &_argc, &_argv, &error)) {
            logemerg("Command line arguments parsing failed: %s", error->message);
        }
    }

}
