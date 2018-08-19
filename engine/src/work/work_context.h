//
// Created by Feo on 16/08/2018.
//

#ifndef ENGINE_WORK_CONTEXT_H
#define ENGINE_WORK_CONTEXT_H

#include "work/work_loop.h"
#include "work/work_service.h"
#include "task/task_router.h"
#include "task/task_handler.h"

namespace engine {

    class work_context : public work_service_provider, public task_handler {
    public:
        FW_DECLARE_SMARTPOINTERS(work_context)
        FW_DELETE_ALL_DEFAULT(work_context)
        FW_CRUCIAL_BASE_DEFINITION()

        using work_service_provider::get_service;

        explicit work_context(const framework::config_setting::sptr& config,
                              const task_router::sptr& router,
                              const work_loop::sptr& loop) noexcept;
        virtual ~work_context() = default;

        void start() noexcept;
        void stop() noexcept;

        void handle_task(const task::sptr& task) noexcept final;

        virtual void setup() noexcept = 0;
        virtual void reset() noexcept = 0;

    protected:
        framework::config_setting::sptr get_config() const noexcept { return _config; }
        task_router::sptr get_router() const noexcept { return _router; }
        work_loop::sptr get_loop() const noexcept { return _loop; }

        void register_task_handler(task::key_type task_key, work_service::key_type service_key) noexcept;

        void add_service(const work_service::sptr& service) noexcept;
        work_service::sptr get_service(work_service::key_type key) const noexcept final;

        template<typename Service>
        void remove_service() noexcept {
            _services[Service::key()].reset();
        }

    private:
        framework::config_setting::sptr                         _config;
        task_router::sptr                                       _router;
        work_loop::sptr                                         _loop;
        std::array<work_service::sptr,
                engine_const::WORK_SERVICE_TYPE_MAX_COUNT>      _services;
        std::array<task::key_type,
                engine_const::TASK_TYPE_MAX_COUNT>              _handler_keys;

    };

}

#endif /* ENGINE_WORK_CONTEXT_H */
