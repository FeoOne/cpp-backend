/**
 * @file engine_option_processor.h
 * @author Feo
 * @date 16/08/2018
 * @brief
 */

#ifndef ENGINE_ENGINE_OPTION_PROCESSOR_H
#define ENGINE_ENGINE_OPTION_PROCESSOR_H

#include <framework.h>

namespace engine {

    class engine_option_processor : public framework::command_line_option_processor {
    public:
        FW_DECLARE_SMARTPOINTERS(engine_option_processor)
        FW_DELETE_ALL_DEFAULT(engine_option_processor)

        explicit engine_option_processor(int argc,
                                         char **argv,
                                         const std::string_view& app_description) noexcept;
        virtual ~engine_option_processor() = default;

    private:
        std::string_view        _config_path;

    };

}

#endif /* ENGINE_ENGINE_OPTION_PROCESSOR_H */
