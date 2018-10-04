/**
 * @file command_line_argument_parser.h
 * @author Feo
 * @date 05/10/2018
 * @brief
 */

#ifndef PMGEN_COMMAND_LINE_ARGUMENT_PARSER_H
#define PMGEN_COMMAND_LINE_ARGUMENT_PARSER_H

#include <stl.h>

class command_line_argument_parser final : public stl::command_line_argument_parser {
public:
    STL_DECLARE_SMARTPOINTERS(command_line_argument_parser)
    STL_DELETE_ALL_DEFAULT(command_line_argument_parser)

    explicit command_line_argument_parser(int argc,
                                          char **argv,
                                          const std::string_view& app_description) noexcept;
    virtual ~command_line_argument_parser() = default;

    const char *input_file() const { return _input; }
    const char *output_file() const { return _output; }

private:
    gchar *         _input;
    gchar *         _output;

};

#endif /* PMGEN_COMMAND_LINE_ARGUMENT_PARSER_H */
