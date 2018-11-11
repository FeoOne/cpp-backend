/**
 * @file application.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include <stl.h>

#include "main/command_line_argument_parser.h"
#include "work/worker_pool.h"
#include "task/task_router.h"

namespace engine {

    class application final {
    public:
        STL_DECLARE_SMARTPOINTERS(application)
        STL_DELETE_ALL_DEFAULT(application)

        using context_creator = std::function<work_context::uptr(const stl::setting&, task_router *)>;

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
        stl::config                                                   _config;
        worker_pool::uptr                                               _pool;
        task_router::uptr                                               _router;

        bool                                                            _need_io_worker;
        bool                                                            _need_db_worker;
        bool                                                            _need_web_worker;

        void process_config() noexcept;

        int start() noexcept;

        void create_queues() noexcept;
        void create_routes() noexcept;
        void create_workers() noexcept;

        void create_single_instance_worker(const std::string_view& name,
                                           const stl::setting& worker_config) noexcept;
        void create_multiple_instance_worker(const std::string_view& name,
                                             const stl::setting& worker_config) noexcept;
    };

}

#endif /* ENGINE_APPLICATION_H */
