/**
 * @file execution_service.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ROCKET_EXECUTION_SERVICE_H
#define ROCKET_EXECUTION_SERVICE_H

#include "task/task_router.h"
#include "work/work_context_delegate.h"

#define RC_BIND_TASK_HANDLER(task, service, routine) \
    add_task_handler(task::key(), std::bind(&service::routine, this, std::placeholders::_1))

namespace rocket {

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
        using task_handler = std::function<void(const task::sptr&)>;

        explicit work_service(const groot::config_setting::sptr& config,
                              const task_router::sptr& router,
                              const work_context_delegate *service_provider) noexcept;

        groot::config_setting::sptr get_config() const noexcept { return _config; }
        task_router::sptr get_router() const noexcept { return _router; }
        const work_context_delegate *get_context_delegate() const noexcept { return _context_delegate; }

        void add_task_handler(task::key_type task_key, task_handler&& handler) noexcept;

    private:
        groot::config_setting::sptr             _config;
        task_router::sptr                           _router;
        const work_context_delegate *               _context_delegate;
        std::array<task_handler,
                consts::TASK_TYPE_MAX_COUNT>  _task_handlers;

    };



}

#endif /* ROCKET_EXECUTION_SERVICE_H */
