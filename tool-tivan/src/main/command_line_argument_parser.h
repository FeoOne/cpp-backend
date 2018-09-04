/**
 * @file command_line_argument_parser.h
 * @author Feo
 * @date 02/09/2018
 * @brief
 */

#ifndef TIVAN_COMMAND_LINE_ARGUMENT_PARSER_H
#define TIVAN_COMMAND_LINE_ARGUMENT_PARSER_H

#include <groot.h>

namespace tivan {

    class command_line_argument_parser : public groot::command_line_argument_parser {
    public:
        GR_DECLARE_SMARTPOINTERS(command_line_argument_parser)
        GR_DELETE_ALL_DEFAULT(command_line_argument_parser)

        command_line_argument_parser(int argc,
                                     char **argv,
                                     const std::string_view& app_description) noexcept;
        virtual ~command_line_argument_parser() = default;

        std::string_view input_file() const noexcept;
        std::string_view output_file() const noexcept;

    private:
        gchar *         _input_file;
        gchar *         _output_file;

    };

}

#endif /* TIVAN_COMMAND_LINE_ARGUMENT_PARSER_H */
