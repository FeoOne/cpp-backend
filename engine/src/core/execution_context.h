/**
 * @file execution_context.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTION_CONTEXT_H
#define ENGINE_EXECUTION_CONTEXT_H

#include <framework.h>

#include "event/event_queue.h"
#include "core/execution_loop.h"
#include "core/execution_service.h"

namespace engine {

    class execution_context {
    public:
        FW_DECLARE_SMARTPOINTERS(execution_context)
        FW_DELETE_ALL_DEFAULT(execution_context)

        virtual ~execution_context();

        void start() noexcept;
        void stop() noexcept;
        void restart() noexcept;

        void join() noexcept;

        template<typename T>
        typename T::sptr get_service() noexcept {
            return std::static_pointer_cast<T>(_get_service(T::key()));
        }

    protected:
        explicit execution_context(execution_loop::uptr&& loop,
                                   const event_queue::sptr& queue,
                                   const framework::config_setting::sptr& config) noexcept;

        framework::config_setting::sptr& config() noexcept { return _config; }

        void _add_service(const execution_service::sptr& service) noexcept;
        void _remove_service(execution_service::key_type key) noexcept;
        execution_service::sptr _get_service(execution_service::key_type key) noexcept;

        virtual void _before_run() noexcept = 0;
        virtual void _after_run() noexcept = 0;

    private:
        using service_map = std::unordered_map<execution_service::key_type, execution_service::sptr>;

        execution_loop::uptr                _loop;
        event_queue::sptr                   _queue;
        framework::config_setting::sptr     _config;
        std::thread                         _thread;
        bool                                _should_restart;

        service_map                         _services;

        void _execute() noexcept;

    };

}

#endif /* ENGINE_EXECUTION_CONTEXT_H */
