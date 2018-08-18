/**
 * @file application.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include <framework.h>

#include "main/engine_option_processor.h"
#include "work/worker_pool.h"
#include "task/task_router.h"

namespace engine {

    class application final {
    public:
        FW_DECLARE_SMARTPOINTERS(application)
        FW_DELETE_ALL_DEFAULT(application)

        explicit application(int argc, char **argv, const std::string_view& description) noexcept;

        /**
         * Entry point.
         * @param argc Command line argument count.
         * @param argv Command line arguments vector.
         * @param description Application description for help output.
         * @return Run status.
         */
        static int start(int argc, char **argv, const std::string_view& description) noexcept;

    private:
        engine_option_processor::uptr   _option_processor;
        framework::config::uptr         _config;
        worker_pool::uptr               _workers;
        task_router::sptr               _router;

        std::unordered_map<work_context::key_type, task_queue::sptr>    _queues;

        int start() noexcept;

        void create_queues() noexcept;
        void create_workers() noexcept;

    };

#if 0
    class application {
    public:
        FW_DECLARE_SMARTPOINTERS(application)

        application();
        virtual ~application();

        void load_config(const std::string_view& filename) noexcept;

        void prepare() noexcept;
        void run() noexcept;

    protected:
        virtual void _before_run() noexcept = 0;
        virtual void _after_run() noexcept = 0;

        void _add_context(const std::string_view &name, const worker::sptr &context) noexcept;
        void _remove_contexts(const std::string_view &name) noexcept;
        std::vector<worker::sptr> _get_contexts(const std::string_view &name) noexcept;

    private:
        using context_map = std::unordered_map<std::string_view, std::vector<worker::sptr>>;
        using event_queue_map = std::unordered_map<std::string_view, event_queue::sptr>;

        framework::config::sptr                 _config;
        context_map                             _contexts;
        event_queue_map                         _queues;
        event_recipient::sptr                   _recipient;

        void _create_contexts() noexcept;
        void _create_event_queues() noexcept;
        void _setup_routes() noexcept;

        worker::sptr _create_job_context(const framework::config_setting::sptr& config) noexcept;
        worker::sptr _create_system_context(const framework::config_setting::sptr& config) noexcept;
        worker::sptr _create_web_server_context(const framework::config_setting::sptr& config) noexcept;

    };
#endif

}

#endif /* ENGINE_APPLICATION_H */
