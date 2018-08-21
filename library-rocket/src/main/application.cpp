/**
 * @file application.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include <groot.h>

#include "main/application.h"
#include "main/rocket_consts.h"
#include "io/io_queue.h"
#include "io/io_context.h"
#include "io/task/new_connection_task.h"
#include "io/task/close_connection_task.h"
#include "io/task/incoming_message_task.h"
#include "io/task/outgoing_message_task.h"
#include "job/job_queue.h"
#include "job/job_context.h"
#include "web/webserver_queue.h"
#include "web/webserver_context.h"
#include "web/task/http_request_task.h"
#include "web/task/http_response_task.h"
#include "system/system_queue.h"
#include "system/system_context.h"

namespace rocket {

    application::application(int argc, char **argv, const std::string_view& description) noexcept :
            _option_processor { engine_option_processor::make_unique(argc, argv, description) },
            _config { groot::config::make_unique() },
            _workers { worker_pool::make_unique() },
            _router { task_router::make_shared() },
            _queues {},
            _context_creators {}
    {
        _context_creators.insert({ consts::WORKER_NAME_IO,
                                   [](const groot::config_setting::sptr& config, const task_router::sptr& router) {
                                       return io_context::make_unique(config, router);
                                   } });
        _context_creators.insert({ consts::WORKER_NAME_SYSTEM,
                                   [](const groot::config_setting::sptr& config, const task_router::sptr& router) {
                                       return system_context::make_unique(config, router);
                                   } });
        _context_creators.insert({ consts::WORKER_NAME_WEBSERVER,
                                   [](const groot::config_setting::sptr& config, const task_router::sptr& router) {
                                       return webserver_context::make_unique(config, router);
                                   } });
    }

    int application::start() noexcept
    {
        _option_processor->parse();
        _config->read(_option_processor->config_path());

        create_queues();
        create_routes();
        create_workers();

        _workers->start();
        _workers->get_worker<system_context>()->join();

        return EXIT_SUCCESS;
    }

    void application::create_queues() noexcept
    {
        _router->add_queue(io_context::key(), io_queue::make_shared());
        _router->add_queue(job_context::key(), job_queue::make_shared());
        _router->add_queue(system_context::key(), system_queue::make_shared());
        _router->add_queue(webserver_context::key(), webserver_queue::make_shared());
    }

    void application::create_routes() noexcept
    {
        // web routes
        _router->register_route(http_request_task::key(), job_context::key());
        _router->register_route(http_response_task::key(), webserver_context::key());

        // io routes
        _router->register_route(new_connection_task::key(), job_context::key());
        _router->register_route(close_connection_task::key(), job_context::key());
        _router->register_route(incoming_message_task::key(), job_context::key());
        _router->register_route(outgoing_message_task::key(), io_context::key());
    }

    void application::create_workers() noexcept
    {
        auto workers_config = (*_config)[consts::CONFIG_KEY_WORKERS];
        for (size_t i = 0; i < workers_config->size(); ++i) {
            auto config { (*workers_config)[i] };
            auto name { (*config)[consts::CONFIG_KEY_NAME]->to_string_view() };
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
        groot::log_manager::setup();
        auto app = application::make_unique(argc, argv, description);
        app->_context_creators.insert({ consts::WORKER_NAME_JOB, std::move(job_context_creator) });
        return app->start();
    }

}
