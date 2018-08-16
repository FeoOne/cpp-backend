//
// Created by Feo on 16/08/2018.
//

#ifndef ENGINE_COMMAND_LINE_ARGUMENT_PARSER_H
#define ENGINE_COMMAND_LINE_ARGUMENT_PARSER_H

#include <glib.h>

#include <framework.h>

namespace engine {

    class command_line_option_parser {
    public:
        FW_DECLARE_SMARTPOINTERS(command_line_option_parser)
        FW_DELETE_ALL_DEFAULT(command_line_option_parser)

        enum option_var_type {
            NONE,
            INT,
            DOUBLE,
            STRING,
            FILENAME,
            STRING_ARRAY,
            FILENAME_ARRAY,
        };

        explicit command_line_option_parser(int argc, char **argv) noexcept;

        void add_option(const std::string_view& long_name,
                        char short_name,
                        option_var_type type,
                        void *pointer,
                        const std::string_view& decription,
                        const std::string_view& argument_decription) noexcept;

        void parse(const std::string_view& app_description) noexcept;

    private:
        int                             _argc;
        char **                         _argv;

        GOptionContext *                _context;
        std::vector<GOptionEntry>       _options;

    };

}

#endif /* ENGINE_COMMAND_LINE_ARGUMENT_PARSER_H */
