/**
 * @file work_service.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ROCKET_EXECUTION_SERVICE_H
#define ROCKET_EXECUTION_SERVICE_H

#include "main/rocket_consts.h"
#include "task/task_router.h"
#include "work/work_service_delegate.h"

#define RC_ASSIGN_TASK_HANDLER(task, service, routine)  \
    assign_task_handler(task::key(), std::bind(&service::routine, this, std::placeholders::_1))

namespace rocket {

    /**
     *
     */
    class work_service {
    public:
        GR_DECLARE_SMARTPOINTERS(work_service)
        GR_DELETE_ALL_DEFAULT(work_service)
        GR_CRUCIAL_BASE_DEFINITION(RC_WORK_SERVICE_TYPE_MAX_KEY)

        virtual ~work_service() = default;

        virtual void setup() noexcept = 0;
        virtual void reset() noexcept = 0;

        void handle_task(basic_task *task) const noexcept;

    protected:
        using task_handler = std::function<void(basic_task *)>;

        explicit work_service(const groot::setting& config,
                              task_router *router,
                              const work_service_delegate *delegate) noexcept;

        const groot::setting& config() const noexcept { return _config; }
        task_router *router() const noexcept { return _router; }
        const work_service_delegate *delegate() const noexcept { return _delegate; }

        void assign_task_handler(basic_task::key_type task_key, task_handler&& handler) noexcept;

    private:
        const groot::setting                    _config;
        task_router *                           _router;
        const work_service_delegate *           _delegate;
        std::array<task_handler, basic_task::MAX_KEY>      _handlers;

    };

}

#endif /* ROCKET_EXECUTION_SERVICE_H */
