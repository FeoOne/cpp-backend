/**
 * @file application.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include <framework.h>

#include "main/engine_const.h"
#include "system/system_context.h"
#include "web/web_server_context.h"

#include "main/application.h"

namespace engine {

    using namespace framework;

    application::application() :
            _config { config::make_shared() },
            _context_map {},
            _context_mutex {}
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
            if (std::strcmp(name, engine_const::SYSTEM_CONTEXT_NAME.data()) == 0) {
                // system_context
                context = system_context::make_shared(specific_context_config);
            } else if (std::strcmp(name, engine_const::WEB_SERVER_CONTEXT_NAME.data()) == 0) {
                // web_server_context
                context = web_server_context::make_shared(specific_context_config);
            }

            _add_execution_context(name, context);
        }
    }

    void application::run() noexcept
    {
        loginfo("Running application...");

        _before_run();

        for (auto& p: _context_map) {
            p.second->start();
        }

        try {
            _context_map[engine_const::SYSTEM_CONTEXT_NAME]->join();
        }
        catch (const std::exception& exception) {
            logemerg("Failed to join system context: %s", exception.what());
        }

        _after_run();
    }

    void application::_add_execution_context(const std::string_view& name,
                                             const execution_context::sptr& context) noexcept
    {
        std::lock_guard<std::timed_mutex> lock(_context_mutex);
        _context_map.insert({ name, context });
    }

    void application::_remove_execution_context(const std::string_view& name) noexcept
    {
        std::lock_guard<std::timed_mutex> lock(_context_mutex);
        _context_map.erase(name);
    }

    execution_context::sptr application::_get_execution_context(const std::string_view& name) noexcept
    {
        std::lock_guard<std::timed_mutex> lock(_context_mutex);
        return _context_map[name];
    }

}
