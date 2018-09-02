/**
 * @file engine_option_processor.h
 * @author Feo
 * @date 16/08/2018
 * @brief
 */

#ifndef ROCKET_ROCKET_OPTION_PROCESSOR_H
#define ROCKET_ROCKET_OPTION_PROCESSOR_H

#include <groot.h>

namespace rocket {

    class command_line_argument_parser : public groot::command_line_argument_parser {
    public:
        GR_DECLARE_SMARTPOINTERS(command_line_argument_parser)
        GR_DELETE_ALL_DEFAULT(command_line_argument_parser)

        explicit command_line_argument_parser(int argc,
                                              char **argv,
                                              const std::string_view& app_description) noexcept;
        virtual ~command_line_argument_parser() = default;

        std::string_view config_path() const noexcept;

    private:
        gchar *         _config_path;

    };

}

#endif /* ROCKET_ROCKET_OPTION_PROCESSOR_H */
