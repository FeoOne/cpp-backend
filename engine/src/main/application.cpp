/**
 * @file application.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include <framework.h>

#include "system/system_context.h"
#include "web/web_server_context.h"

#include "main/application.h"

namespace engine {

    using namespace framework;

    application::application() :
            _config { config::make_shared() }
    {
        log_manager::setup();
    }

    application::~application()
    {
        loginfo("Application stopped.");
    }

    void application::load_config(const std::string_view& filename) noexcept
    {
        loginfo("Loading config: %s", filename.data());
        _config->read(filename);
    }

    void application::prepare() noexcept
    {
        loginfo("Prepearing to run application...");

        auto context_config = (*_config)["context"];
        for (size_t i = 0; i < context_config->size(); ++i) {
            execution_context::sptr context { nullptr };

            auto specific_context_config = (*context_config)[i];
            auto name = (*specific_context_config)["name"]->to_string();
            if (std::strcmp(name, system_context::NAME.data()) == 0) {
                // system_context
                context = system_context::make_shared(specific_context_config);
            } else if (std::strcmp(name, web_server_context::NAME.data()) == 0) {
                // web_server_context
                context = web_server_context::make_shared(specific_context_config);
            }

            _context_map[name] = context;
            _context_vector.push_back(context);
        }
    }

    void application::run() noexcept
    {
        loginfo("Running application...");

        for (auto& context: _context_vector) {
            context->start();
        }

        _context_map[system_context::NAME]->join();
    }

}
