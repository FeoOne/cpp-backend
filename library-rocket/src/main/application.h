/**
 * @file application.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ROCKET_APPLICATION_H
#define ROCKET_APPLICATION_H

#include <groot.h>

#include "main/command_line_argument_parser.h"
#include "work/worker_pool.h"
#include "task/task_router.h"

namespace rocket {

    class application final {
    public:
        GR_DECLARE_SMARTPOINTERS(application)
        GR_DELETE_ALL_DEFAULT(application)

        using context_creator = std::function<work_context::uptr(const groot::setting&, task_router *)>;

        explicit application(int argc, char **argv, const std::string_view& description) noexcept;

        /**
         * Entry point.
         * @param argc Command line argument count.
         * @param argv Command line argument vector.
         * @param description Application description for help output.
         * @return Run status.
         */
        static int start(int argc,
                         char **argv,
                         context_creator&& job_context_creator,
                         const std::string_view& description) noexcept;

    private:
        command_line_argument_parser::uptr                              _argument_parser;
        std::unordered_map<std::string_view, context_creator>           _context_creators;
        groot::config                                                   _config;
        worker_pool::uptr                                               _pool;
        task_router::uptr                                               _router;

        int start() noexcept;

        void create_queues() noexcept;
        void create_routes() noexcept;
        void create_workers() noexcept;

        void assign_context_creator(const std::string_view& name, context_creator&& creator) noexcept;

    };

}

#endif /* ROCKET_APPLICATION_H */
