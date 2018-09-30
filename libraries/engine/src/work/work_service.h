/**
 * @file work_service.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTION_SERVICE_H
#define ENGINE_EXECUTION_SERVICE_H

#include "main/engine_consts.h"
#include "task/task_router.h"
#include "work/work_service_delegate.h"

#define EX_ASSIGN_TASK_HANDLER(task, service, routine)  \
    assign_task_handler(task::key(), std::bind(&service::routine, this, std::placeholders::_1))

namespace engine {

    /**
     *
     */
    class work_service {
    public:
        STL_DECLARE_SMARTPOINTERS(work_service)
        STL_DELETE_ALL_DEFAULT(work_service)
        STL_CRUCIAL_BASE_DEFINITION(EX_WORK_SERVICE_TYPE_MAX_KEY)

        virtual ~work_service() = default;

        virtual void setup() noexcept = 0;
        virtual void reset() noexcept = 0;

        void handle_task(basic_task *task) const noexcept;

    protected:
        using task_handler = std::function<void(basic_task *)>;

        explicit work_service(const stl::setting& config,
                              task_router *router,
                              const work_service_delegate *delegate) noexcept;

        const stl::setting& config() const noexcept { return _config; }
        task_router *router() const noexcept { return _router; }
        const work_service_delegate *delegate() const noexcept { return _delegate; }

        void assign_task_handler(basic_task::key_type task_key, task_handler&& handler) noexcept;

    private:
        const stl::setting                            _config;
        task_router *                                   _router;
        const work_service_delegate *                   _delegate;
        std::array<task_handler, basic_task::MAX_KEY>   _handlers;

    };

}

#endif /* ENGINE_EXECUTION_SERVICE_H */
