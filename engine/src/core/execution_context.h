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
#include "event/event_recipient.h"
#include "core/execution_loop.h"
#include "core/execution_service.h"

namespace engine {

    class execution_context : public std::enable_shared_from_this<execution_context> {
    public:
        FW_DECLARE_SMARTPOINTERS(execution_context)
        FW_DELETE_ALL_DEFAULT(execution_context)

        virtual ~execution_context() = default;

        void start() noexcept;
        void stop() noexcept;
        void restart() noexcept;

        void join() noexcept;

        std::string_view name() const noexcept;

        template<typename T>
        typename T::sptr get_service() noexcept {
            return std::static_pointer_cast<T>(get_service(T::key()));
        }

    protected:
        explicit execution_context(execution_loop::uptr&& loop,
                                   const event_queue::sptr& queue,
                                   const event_recipient::sptr& recipient,
                                   const framework::config_setting::sptr& config) noexcept;

        framework::config_setting::sptr& get_config() noexcept { return _config; }
        event_queue::sptr get_queue() noexcept { return _queue; }
        event_recipient::sptr get_recipient() noexcept { return _recipient; }

        void add_service(const execution_service::sptr &service) noexcept;
        void remove_service(execution_service::key_type key) noexcept;
        execution_service::sptr get_service(execution_service::key_type key) noexcept;

        virtual void before_run() noexcept = 0;
        virtual void after_run() noexcept = 0;

    private:
        using service_map = std::unordered_map<execution_service::key_type, execution_service::sptr>;

        std::thread                         _thread;
        execution_loop::uptr                _loop;
        bool                                _should_restart;
        event_queue::sptr                   _queue;
        event_recipient::sptr               _recipient;
        framework::config_setting::sptr     _config;

        service_map                         _services;

        void _execute() noexcept;

        void _notify_about_start() noexcept;

    };

}

#endif /* ENGINE_EXECUTION_CONTEXT_H */
