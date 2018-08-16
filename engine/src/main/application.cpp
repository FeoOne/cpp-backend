/**
 * @file application.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include <framework.h>

#include "events/events.h"
#include "main/engine_const.h"
#include "job/job_context.h"
#include "system/system_context.h"
#include "web/web_server_context.h"

#include "main/application.h"

namespace engine {

    using namespace framework;

    application::application(int argc, char **argv)
    {
    }

#if 0
    application::application() :
            _config { config::make_shared() },
            _contexts {},
            _queues {},
            _recipient { event_recipient::make_shared() }
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

        _create_event_queues();
        _create_contexts();
        _setup_routes();
    }

    void application::run() noexcept
    {
        loginfo("Running application...");

        _before_run();

        for (auto& pair: _contexts) {
            for (auto& context: pair.second) {
                context->start();
            }
        }

        _get_contexts(engine_const::SYSTEM_CONTEXT_NAME)[0]->join();

        _after_run();
    }

    void application::_add_context(const std::string_view &name,
                                   const worker::sptr &context) noexcept
    {
        _contexts[name].push_back(context);
    }

    void application::_remove_contexts(const std::string_view &name) noexcept
    {
        _contexts.erase(name);
    }

    std::vector<worker::sptr> application::_get_contexts(const std::string_view &name) noexcept
    {
        return _contexts[name];
    }

    void application::_create_contexts() noexcept
    {
#define ADD_ENTRY(n, m)         { engine_const::n, std::bind(&application::m, this, std::placeholders::_1) }

        std::unordered_map<std::string_view,
                           std::function<worker::sptr(const config_setting::sptr&)>> functors {
            ADD_ENTRY(JOB_CONTEXT_NAME, _create_job_context),
            ADD_ENTRY(SYSTEM_CONTEXT_NAME, _create_system_context),
            ADD_ENTRY(WEB_SERVER_CONTEXT_NAME, _create_web_server_context)
        };

#undef ADD_ENTRY

        auto context_config = (*_config)["context"];
        for (size_t i = 0; i < context_config->size(); ++i) {
            auto config { (*context_config)[i] };
            std::string_view name { (*config )["name"]->to_string() };

            auto context { functors[name](config) };

            _add_context(name, context);
        }
    }

    void application::_create_event_queues() noexcept
    {
#define INSERT_QUEUE(n, c)      _queues.insert({ engine_const::n, c::make_shared() })

        INSERT_QUEUE(JOB_CONTEXT_NAME, job_event_queue);
        INSERT_QUEUE(SYSTEM_CONTEXT_NAME, system_event_queue);
        INSERT_QUEUE(WEB_SERVER_CONTEXT_NAME, web_server_event_queue);

#undef INSERT_QUEUE
    }

    void application::_setup_routes() noexcept
    {
        event_queue::sptr queue;
        {
            // job
            queue = _queues[engine_const::JOB_CONTEXT_NAME];

            _recipient->add_route(context_did_start_event::key(), queue);
        }
    }

    worker::sptr application::_create_job_context(const config_setting::sptr& config) noexcept
    {
        return job_context::make_shared(_queues[engine_const::JOB_CONTEXT_NAME], _recipient, config);
    }

    worker::sptr application::_create_system_context(const config_setting::sptr& config) noexcept
    {
        return system_context::make_shared(_queues[engine_const::SYSTEM_CONTEXT_NAME], _recipient, config);
    }

    worker::sptr application::_create_web_server_context(const config_setting::sptr& config) noexcept
    {
        return web_server_context::make_shared(_queues[engine_const::WEB_SERVER_CONTEXT_NAME], _recipient, config);
    }
#endif
}
