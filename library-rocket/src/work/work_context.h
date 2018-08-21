//
// Created by Feo on 16/08/2018.
//

#ifndef ROCKET_WORK_CONTEXT_H
#define ROCKET_WORK_CONTEXT_H

#include "task/task_router.h"
#include "task/task_handler.h"
#include "work/work_loop.h"
#include "work/work_service.h"
#include "work/work_context_delegate.h"

namespace rocket {

    class work_context : public work_context_delegate, public task_handler {
    public:
        FW_DECLARE_SMARTPOINTERS(work_context)
        FW_DELETE_ALL_DEFAULT(work_context)
        FW_CRUCIAL_BASE_DEFINITION()

        using work_context_delegate::get_service;

        explicit work_context(const groot::config_setting::sptr& config,
                              const task_router::sptr& router,
                              const work_loop::sptr& loop) noexcept;
        virtual ~work_context() = default;

        void start() noexcept;
        void stop() noexcept;

        void handle_task(const task::sptr& task) noexcept final;

        virtual void setup() noexcept = 0;
        virtual void reset() noexcept = 0;

    protected:
        groot::config_setting::sptr get_config() const noexcept { return _config; }
        task_router::sptr get_router() const noexcept { return _router; }
        work_loop::sptr get_loop() const noexcept final { return _loop; }

        void register_task_handler(task::key_type task_key, work_service::key_type service_key) noexcept;

        void add_service(const work_service::sptr& service) noexcept;
        work_service::sptr get_service(work_service::key_type key) const noexcept final;

        template<typename Service>
        void remove_service() noexcept {
            _services[Service::key()].reset();
        }

    private:
        groot::config_setting::sptr                         _config;
        task_router::sptr                                       _router;
        work_loop::sptr                                         _loop;
        std::array<work_service::sptr,
                consts::WORK_SERVICE_TYPE_MAX_COUNT>      _services;
        std::array<task::key_type,
                consts::TASK_TYPE_MAX_COUNT>              _handler_keys;

    };

}

#endif /* ROCKET_WORK_CONTEXT_H */
