/**
 * @file execution_context.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ROCKET_EXECUTION_CONTEXT_H
#define ROCKET_EXECUTION_CONTEXT_H

#if __APPLE__
#include <pthread/pthread.h>
#else
#include <pthread.h>
#endif

#include <groot.h>

#include "work/work_context.h"

namespace rocket {

    class worker final {
    public:
        FW_DECLARE_SMARTPOINTERS(worker)
        FW_DELETE_ALL_DEFAULT(worker)

        enum class detach_state {
            JOINABLE,
            DETACHED,
        };

        explicit worker(const groot::config_setting::sptr& config, work_context::uptr&& context) noexcept;
        ~worker();

        void start(detach_state state) noexcept;
        void stop() noexcept;

        void restart() noexcept;

        void join() noexcept;

    private:
        friend class worker_pool;

        pthread_t                           _thread;
        groot::config_setting::sptr     _config;
        work_context::uptr                  _context;
        bool                                _should_restart;

        void exec_routine() noexcept;

        static void *exec_routine(void *ptr) noexcept;

    };

#if 0
    class worker : public std::enable_shared_from_this<worker> {
    public:
        FW_DECLARE_SMARTPOINTERS(worker)
        FW_DELETE_ALL_DEFAULT(worker)

        virtual ~worker() = default;

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
        explicit worker(work_loop::uptr&& loop,
                                   const event_queue::sptr& queue,
                                   const event_recipient::sptr& recipient,
                                   const groot::config_setting::sptr& config) noexcept;

        groot::config_setting::sptr& get_config() noexcept { return _config; }
        event_queue::sptr get_queue() noexcept { return _queue; }
        event_recipient::sptr get_recipient() noexcept { return _recipient; }

        void add_service(const work_service::sptr &service) noexcept;
        void remove_service(work_service::key_type key) noexcept;
        work_service::sptr get_service(work_service::key_type key) noexcept;

        virtual void before_run() noexcept = 0;
        virtual void after_run() noexcept = 0;

    private:
        using service_map = std::unordered_map<work_service::key_type, work_service::sptr>;

        std::thread                         _thread;
        work_loop::uptr                _loop;
        bool                                _should_restart;
        event_queue::sptr                   _queue;
        event_recipient::sptr               _recipient;
        groot::config_setting::sptr     _config;

        service_map                         _services;

        void _execute() noexcept;

        void _notify_about_start() noexcept;

    };
#endif

}

#endif /* ROCKET_EXECUTION_CONTEXT_H */
