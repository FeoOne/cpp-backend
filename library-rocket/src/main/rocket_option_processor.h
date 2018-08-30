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

    class rocket_option_processor : public groot::command_line_option_processor {
    public:
        GR_DECLARE_SMARTPOINTERS(rocket_option_processor)
        GR_DELETE_ALL_DEFAULT(rocket_option_processor)

        explicit rocket_option_processor(int argc,
                                         char **argv,
                                         const std::string_view& app_description) noexcept;
        virtual ~rocket_option_processor() = default;

        std::string_view config_path() const noexcept;

    private:
        gchar *         _config_path;

    };

}

#endif /* ROCKET_ROCKET_OPTION_PROCESSOR_H */
