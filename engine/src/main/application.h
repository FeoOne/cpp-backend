/**
 * @file application.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include <framework.h>

#include "core/execution_context.h"
#include "event/event_router.h"

namespace engine {

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

        void _add_context(const std::string_view &name, const execution_context::sptr &context) noexcept;
        void _remove_context(const std::string_view &name) noexcept;
        std::vector<execution_context::sptr> _get_contexts(const std::string_view &name) noexcept;

    private:
        using context_map = std::unordered_map<std::string_view, std::vector<execution_context::sptr>>;
        using event_queue_map = std::unordered_map<std::string_view, event_queue::sptr>;

        framework::config::sptr                 _config;
        context_map                             _contexts;
        event_queue_map                         _queues;
        event_router::uptr                      _router;

        void _create_contexts() noexcept;
        void _create_event_queues() noexcept;

        execution_context::sptr _create_job_context(const framework::config_setting::sptr& config) noexcept;
        execution_context::sptr _create_system_context(const framework::config_setting::sptr& config) noexcept;
        execution_context::sptr _create_web_server_context(const framework::config_setting::sptr& config) noexcept;

    };

}

#endif /* ENGINE_APPLICATION_H */
