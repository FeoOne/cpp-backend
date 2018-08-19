/**
 * @file execution_service.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTION_SERVICE_H
#define ENGINE_EXECUTION_SERVICE_H

#include "task/task_router.h"

namespace engine {

    class work_service;

    class work_service_provider {
    public:
        FW_DECLARE_SMARTPOINTERS(work_service_provider)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(work_service_provider)

        virtual ~work_service_provider() = default;

        template<typename Service>
        typename Service::sptr get_service() const noexcept {
            return std::static_pointer_cast<Service>(get_service(Service::key()));
        }

    protected:
        work_service_provider() = default;

        virtual std::shared_ptr<work_service> get_service(framework::crucial_key_type key) const noexcept = 0;

    };

    class work_service {
    public:
        FW_DECLARE_SMARTPOINTERS(work_service)
        FW_DELETE_ALL_DEFAULT(work_service)
        FW_CRUCIAL_BASE_DEFINITION()

        virtual ~work_service() = default;

        virtual void setup() noexcept = 0;
        virtual void reset() noexcept = 0;

        void handle_task(const task::sptr& task) noexcept;

    protected:
        using task_handler = std::function<void(const task::sptr&)>;

        explicit work_service(const framework::config_setting::sptr& config,
                              const task_router::sptr& router,
                              const work_service_provider *service_provider) noexcept;

        framework::config_setting::sptr get_config() const noexcept { return _config; }
        task_router::sptr get_router() const noexcept { return _router; }
        const work_service_provider *get_service_provider() const noexcept { return _service_provider; }

        void add_task_handler(task::key_type task_key, task_handler&& handler) noexcept;

    private:
        framework::config_setting::sptr             _config;
        task_router::sptr                           _router;
        const work_service_provider *               _service_provider;
        std::array<task_handler,
                engine_const::TASK_TYPE_MAX_COUNT>  _task_handlers;

    };



}

#endif /* ENGINE_EXECUTION_SERVICE_H */
