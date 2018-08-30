/**
 * @file execution_service.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ROCKET_EXECUTION_SERVICE_H
#define ROCKET_EXECUTION_SERVICE_H

#include "task/task_router.h"
#include "work/work_service_delegate.h"

#define RC_BIND_TASK_HANDLER(task, service, routine) \
    assign_task_handler(task::key(), std::bind(&service::routine, this, std::placeholders::_1))

namespace rocket {

    /**
     *
     */
    class work_service {
    public:
        GR_DECLARE_SMARTPOINTERS(work_service)
        GR_DELETE_ALL_DEFAULT(work_service)
        GR_CRUCIAL_BASE_DEFINITION()

        virtual ~work_service() = default;

        virtual void setup() noexcept = 0;
        virtual void reset() noexcept = 0;

        void handle_task(const task::sptr& task) noexcept;

    protected:
        using handler = std::function<void(const task::sptr&)>;

        explicit work_service(const groot::config_setting::sptr& config,
                              const task_router::sptr& router,
                              const work_service_delegate *delegate) noexcept;

        groot::config_setting::sptr get_config() const noexcept { return _config; }
        task_router::sptr get_router() const noexcept { return _router; }
        const work_service_delegate *get_delegate() const noexcept { return _delegate; }

        void assign_task_handler(task::key_type task_key, handler&& handler) noexcept;

    private:
        groot::config_setting::sptr                             _config;
        task_router::sptr                                       _router;
        const work_service_delegate *                           _delegate;
        std::array<handler, consts::TASK_TYPE_MAX_COUNT>        _handlers;

    };

}

#endif /* ROCKET_EXECUTION_SERVICE_H */
