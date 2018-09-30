/**
 * @file engine_option_processor.h
 * @author Feo
 * @date 16/08/2018
 * @brief
 */

#ifndef ENGINE_ENGINE_OPTION_PROCESSOR_H
#define ENGINE_ENGINE_OPTION_PROCESSOR_H

#include <stl.h>

namespace engine {

    class command_line_argument_parser : public stl::command_line_argument_parser {
    public:
        STL_DECLARE_SMARTPOINTERS(command_line_argument_parser)
        STL_DELETE_ALL_DEFAULT(command_line_argument_parser)

        explicit command_line_argument_parser(int argc,
                                              char **argv,
                                              const std::string_view& app_description) noexcept;
        virtual ~command_line_argument_parser() = default;

        std::string_view config_path() const noexcept;

    private:
        gchar *         _config_path;

    };

}

#endif /* ENGINE_ENGINE_OPTION_PROCESSOR_H */
