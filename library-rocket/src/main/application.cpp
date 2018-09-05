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
#include "web/task/ws_incoming_message_task.h"
#include "web/task/ws_outgoing_message_task.h"
#include "system/system_queue.h"
#include "system/system_context.h"

using namespace std::chrono_literals;

namespace rocket {

    application::application(int argc, char **argv, const std::string_view& description) noexcept :
            _argument_parser { command_line_argument_parser::make_unique(argc, argv, description) },
            _context_creators {},
            _config {},
            _pool { worker_pool::make_unique() },
            _router { task_router::make_unique() }
    {
        assign_context_creator(consts::WORKER_NAME_IO,
                               [](const groot::setting& config, task_router *router) {
                                   return io_context::make_unique(config, router);
                               });
        assign_context_creator(consts::WORKER_NAME_SYSTEM,
                               [](const groot::setting& config, task_router *router) {
                                   return system_context::make_unique(config, router);
                               });
        assign_context_creator(consts::WORKER_NAME_WEBSERVER,
                               [](const groot::setting& config, task_router *router) {
                                   return webserver_context::make_unique(config, router);
                               });
    }

    int application::start() noexcept
    {
        _argument_parser->parse();

        _config.load(_argument_parser->config_path());

        create_queues();
        create_routes();
        create_workers();

        _pool->start();

        /* There are no more work for main thread,
         * so join to system worker to keep process alive.
         */
        auto &system_workers = _pool->get_workers<system_context>();
        logassert(system_workers.size() == 1, "System worker count can't be other than 1.");
        system_workers.front()->join();

        return EXIT_SUCCESS;
    }

    void application::create_queues() noexcept
    {
        _router->add_queue(io_context::key(), io_queue::make_unique());
        _router->add_queue(job_context::key(), job_queue::make_unique());
        _router->add_queue(system_context::key(), system_queue::make_unique());
        _router->add_queue(webserver_context::key(), webserver_queue::make_unique());
    }

    void application::create_routes() noexcept
    {
        // web routes
        _router->assign_route(http_request_task::key(), job_context::key());
        _router->assign_route(http_response_task::key(), webserver_context::key());
        _router->assign_route(ws_incoming_message_task::key(), job_context::key());
        _router->assign_route(ws_outgoing_message_task::key(), webserver_context::key());

        // io routes
        _router->assign_route(new_connection_task::key(), job_context::key());
        _router->assign_route(close_connection_task::key(), job_context::key());
        _router->assign_route(incoming_message_task::key(), job_context::key());
        _router->assign_route(outgoing_message_task::key(), io_context::key());
    }

    void application::create_workers() noexcept
    {
        auto workers_config = _config[consts::CONFIG_KEY_WORKERS];
        for (size_t i = 0; i < workers_config.size(); ++i) {
            auto config { workers_config[i] };
            auto name { config[consts::CONFIG_KEY_NAME].to_string() };
            auto context { _context_creators[name](config, _router.get()) };

            _pool->push(worker::make_unique(config, std::move(context)));
        }

        _context_creators.clear();
    }

    void application::assign_context_creator(const std::string_view& name, context_creator&& creator) noexcept
    {
        _context_creators.insert({ name, std::move(creator) });
    }

    // static
    int application::start(int argc,
                           char **argv,
                           context_creator&& job_context_creator,
                           const std::string_view& description) noexcept
    {
        groot::log_manager::setup();
        auto app = application::make_unique(argc, argv, description);
        app->assign_context_creator(consts::WORKER_NAME_JOB, std::move(job_context_creator));
        return app->start();
    }

}
