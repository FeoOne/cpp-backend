/**
 * @file application.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ROCKET_APPLICATION_H
#define ROCKET_APPLICATION_H

#include <groot.h>

#include "main/engine_option_processor.h"
#include "work/worker_pool.h"
#include "task/task_router.h"

namespace rocket {

    class application final {
    public:
        FW_DECLARE_SMARTPOINTERS(application)
        FW_DELETE_ALL_DEFAULT(application)

        using context_creator = std::function<work_context::uptr(const groot::config_setting::sptr&,
                                                                 const task_router::sptr&)>;

        explicit application(int argc, char **argv, const std::string_view& description) noexcept;

        /**
         * Entry point.
         * @param argc Command line argument count.
         * @param argv Command line arguments vector.
         * @param description Application description for help output.
         * @return Run status.
         */
        static int start(int argc,
                         char **argv,
                         context_creator&& job_context_creator,
                         const std::string_view& description) noexcept;

    private:
        engine_option_processor::uptr                                   _option_processor;
        groot::config::uptr                                         _config;
        worker_pool::uptr                                               _workers;
        task_router::sptr                                               _router;
        std::unordered_map<work_context::key_type, task_queue::sptr>    _queues;
        std::unordered_map<std::string_view, context_creator>           _context_creators;

        int start() noexcept;

        void create_queues() noexcept;
        void create_routes() noexcept;
        void create_workers() noexcept;

    };

}

#endif /* ROCKET_APPLICATION_H */
