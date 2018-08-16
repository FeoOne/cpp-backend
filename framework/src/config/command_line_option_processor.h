//
// Created by Feo on 16/08/2018.
//

#ifndef FRAMEWORK_COMMAND_LINE_ARGUMENT_PARSER_H
#define FRAMEWORK_COMMAND_LINE_ARGUMENT_PARSER_H

#include <queue>
#include <vector>
#include <unordered_map>

#include <glib.h>

#include "memory/memory.h"
#include "string/string.h"

namespace framework {

    enum command_line_option_type {
        NONE,
        INT,
        DOUBLE,
        STRING,
        FILENAME,
        STRING_ARRAY,
        FILENAME_ARRAY,
    };

    class command_line_option_processor {
    public:
        FW_DECLARE_SMARTPOINTERS(command_line_option_processor)
        FW_DELETE_ALL_DEFAULT(command_line_option_processor)

        virtual ~command_line_option_processor();

        void parse() noexcept;

    protected:
        explicit command_line_option_processor(int argc,
                                               char **argv,
                                               const std::string_view& app_description) noexcept;

        void push_group(const std::string_view& name,
                        const std::string_view& description,
                        const std::string_view& detailed_description) noexcept;

        void add_option(command_line_option_type type,
                        void *ptr,
                        const std::string_view& long_name,
                        char short_name,
                        const std::string_view& description,
                        const std::string_view& arg_description,
                        bool is_optional,
                        bool is_hidden) noexcept;

    private:
        int                                                             _argc;
        char **                                                         _argv;

        std::queue<GOptionGroup *>                                      _groups;
        GOptionContext *                                                _context;
        std::unordered_map<GOptionGroup *, std::vector<GOptionEntry>>   _options;

    };

}

#endif /* FRAMEWORK_COMMAND_LINE_ARGUMENT_PARSER_H */
