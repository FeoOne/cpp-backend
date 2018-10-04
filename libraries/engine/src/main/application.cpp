/**
 * @file application.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include <stl.h>

#include "main/application.h"
#include "main/engine_consts.h"
#include "task/queue/quiet_task_queue.h"
#include "task/queue/condition_task_queue.h"
#include "context/io/io_context.h"
#include "context/io/task/connection_status_changed_task.h"
#include "context/io/task/io_request_task.h"
#include "context/io/task/io_response_task.h"
#include "context/db/db_context.h"
#include "context/db/task/db_request_task.h"
#include "context/db/task/db_response_task.h"
#include "context/job/job_context.h"
#include "context/web/web_context.h"
#include "context/web/task/http_request_task.h"
#include "context/web/task/http_response_task.h"
#include "context/web/task/ws_incoming_message_task.h"
#include "context/web/task/ws_outgoing_message_task.h"
#include "context/system/system_context.h"

#define EX_ADD_QUEUE(context, queue)    _router->add_queue(context::key(), queue::make_unique())
#define EX_ASSIGN_ROUTE(task, context)  _router->assign_route(task::key(), context::key())
#define EX_ASSIGN_CONTEXT_CREATOR(name, context)                                        \
    _context_creators.insert({ name,                                                    \
                             [](const stl::setting& config, task_router *router) {    \
                                 return context::make_unique(config, router);           \
                             } })

namespace engine {

    application::application(int argc, char **argv, const std::string_view& description) noexcept :
            _argument_parser { command_line_argument_parser::make_unique(argc, argv, description) },
            _context_creators {},
            _config {},
            _pool { worker_pool::make_unique() },
            _router { task_router::make_unique() },
            _need_io_worker { false },
            _need_db_worker { false },
            _need_web_worker { false }
    {
        EX_ASSIGN_CONTEXT_CREATOR(consts::WORKER_NAME_IO, io_context);
        EX_ASSIGN_CONTEXT_CREATOR(consts::WORKER_NAME_DB, db_context);
        EX_ASSIGN_CONTEXT_CREATOR(consts::WORKER_NAME_WEB, web_context);
        EX_ASSIGN_CONTEXT_CREATOR(consts::WORKER_NAME_SYSTEM, system_context);
    }

    int application::start() noexcept
    {
        _argument_parser->parse();

        process_config();

        create_queues();
        create_routes();
        create_workers();

        _pool->start();

        // There are no more work for main thread,
        // so join to system worker to keep process alive.
        auto& system_workers = _pool->get_workers<system_context>();
        logassert(system_workers.size() == 1, "System worker count can't be other than 1.");
        system_workers.front()->join();

        return EXIT_SUCCESS;
    }

    void application::create_queues() noexcept
    {
        // required
        EX_ADD_QUEUE(job_context, condition_task_queue);
        EX_ADD_QUEUE(system_context, condition_task_queue);

        // optional
        if (_need_io_worker) {
            EX_ADD_QUEUE(io_context, quiet_task_queue);
        }
        if (_need_db_worker) {
            EX_ADD_QUEUE(db_context, quiet_task_queue);
        }
        if (_need_web_worker) {
            EX_ADD_QUEUE(web_context, quiet_task_queue);
        }
    }

    void application::create_routes() noexcept
    {
        // io routes
        if (_need_io_worker) {
            EX_ASSIGN_ROUTE(connection_status_changed_task, job_context);
            EX_ASSIGN_ROUTE(io_request_task, job_context);
            EX_ASSIGN_ROUTE(io_response_task, io_context);
        }

        // db routes
        if (_need_db_worker) {
            EX_ASSIGN_ROUTE(db_request_task, db_context);
            EX_ASSIGN_ROUTE(db_response_task, job_context);
        }

        // web routes
        if (_need_web_worker) {
            EX_ASSIGN_ROUTE(http_request_task, job_context);
            EX_ASSIGN_ROUTE(http_response_task, web_context);
            EX_ASSIGN_ROUTE(ws_incoming_message_task, job_context);
            EX_ASSIGN_ROUTE(ws_outgoing_message_task, web_context);
        }
    }

    void application::create_workers() noexcept
    {
        auto workers_config { _config[consts::config::key::WORKERS] };
        for (size_t i = 0; i < workers_config.size(); ++i) {
            auto worker_config { workers_config[i] };
            auto name { worker_config[consts::config::key::NAME].to_string() };

            if (name == consts::WORKER_NAME_JOB) {
                create_multiple_instance_worker(name, worker_config);
            } else {
                create_single_instance_worker(name, worker_config);
            }
        }

        _context_creators.clear();
    }

    void application::create_single_instance_worker(const std::string_view& name,
                                                    const stl::setting& worker_config) noexcept
    {
        auto context { _context_creators[name](worker_config, _router.get()) };

        _pool->push(worker::make_unique(worker_config, std::move(context)));
    }

    void application::create_multiple_instance_worker(const std::string_view& name,
                                                      const stl::setting& worker_config) noexcept
    {
        auto count { worker_config[consts::config::key::COUNT].to_int32<size_t>() };
        for (size_t i = 0; i < count; ++i) {
            auto context { _context_creators[name](worker_config, _router.get()) };

            _pool->push(worker::make_unique(worker_config, std::move(context)));
        }
    }

    void application::process_config() noexcept
    {
        _config.load(_argument_parser->config_path());

        // Determine which optional workers must be initialized
        auto workers_config { _config[consts::config::key::WORKERS] };
        for (size_t i = 0; i < workers_config.size(); ++i) {
            auto config { workers_config[i] };
            auto name { config[consts::config::key::NAME].to_string() };

            if (name == consts::WORKER_NAME_IO) {
                _need_io_worker = true;
            } else if (name == consts::WORKER_NAME_DB) {
                _need_db_worker = true;
            } else if (name == consts::WORKER_NAME_WEB) {
                _need_web_worker = true;
            }
        }
    }

    // static
    int application::start(int argc,
                           char **argv,
                           context_creator&& job_context_creator,
                           const std::string_view& description) noexcept
    {
        // Pre-initialize systems
        stl::log_manager::setup();

#ifndef NDEBUG
        // Print hardware info
        stl::hardware::print_info();
#endif

        // Create and start application
        auto app { application::make_unique(argc, argv, description) };
        // Add user-defined job context creator
        app->_context_creators.insert({ consts::WORKER_NAME_JOB, std::move(job_context_creator) });
        return app->start();
    }

}

#undef EX_ASSIGN_CONTEXT_CREATOR
#undef EX_ASSIGN_ROUTE
#undef EX_ADD_QUEUE
