/**
 * @file application.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include <framework.h>

#include "main/application.h"
#include "main/engine_const.h"
#include "job/job_queue.h"
#include "job/job_context.h"
#include "web/webserver_queue.h"
#include "web/webserver_context.h"
#include "web/task/http_request_task.h"
#include "web/task/http_response_task.h"
#include "system/system_queue.h"
#include "system/system_context.h"

namespace engine {

    using namespace framework;

    application::application(int argc, char **argv, const std::string_view& description) noexcept :
            _option_processor { engine_option_processor::make_unique(argc, argv, description) },
            _config { config::make_unique() },
            _workers { worker_pool::make_unique() },
            _router { task_router::make_shared() },
            _context_creators {},
            _queues {}
    {
        _context_creators.insert({ engine_const::WORKER_NAME_SYSTEM,
                                   [](const config_setting::sptr& config, const task_router::sptr& router) {
                                       return system_context::make_unique(config, router);
                                   } });
        _context_creators.insert({ engine_const::WORKER_NAME_WEBSERVER,
                                   [](const config_setting::sptr& config, const task_router::sptr& router) {
                                       return webserver_context::make_unique(config, router);
                                   } });
    }

    int application::start() noexcept
    {
        _option_processor->parse();
        _config->read(_option_processor->config_path());

        create_queues();
        create_workers();

        _workers->start();
        _workers->get_worker<system_context>()->join();

        return EXIT_SUCCESS;
    }

    void application::create_queues() noexcept
    {
        _router->add_queue(job_context::key(), job_queue::make_shared());
        _router->add_queue(system_context::key(), system_queue::make_shared());
        _router->add_queue(webserver_context::key(), webserver_queue::make_shared());

        _router->register_route(http_request_task::key(), job_context::key());
        _router->register_route(http_response_task::key(), webserver_context::key());
    }

    void application::create_workers() noexcept
    {
        auto workers_config = (*_config)[engine_const::CONFIG_KEY_WORKERS];
        for (size_t i = 0; i < workers_config->size(); ++i) {
            auto config { (*workers_config)[i] };
            auto name { (*config)[engine_const::CONFIG_KEY_NAME]->to_string_view() };
            auto context { _context_creators.at(name)(config, _router) };

            _workers->push(worker::make_unique(config, std::move(context)));
        }
    }

    // static
    int application::start(int argc,
                           char **argv,
                           context_creator&& job_context_creator,
                           const std::string_view& description) noexcept
    {
        log_manager::setup();
        auto app = application::make_unique(argc, argv, description);
        app->_context_creators.insert({ engine_const::WORKER_NAME_JOB, std::move(job_context_creator) });
        return app->start();
    }

}
