/**
 * @file execution_service.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "work/service/work_service.h"

namespace engine {

    STL_CRUCIAL_BASE_DECLARATION(work_service)

    work_service::work_service(const stl::setting& config,
                               task_router *router,
                               const work_service_delegate *delegate) noexcept :
            _config { config },
            _router { router },
            _delegate { delegate },
            _handlers {}
    {
    }

    void work_service::handle_task(basic_task *task) const noexcept
    {
#ifdef NDEBUG
        _handlers[task->get_key()](task);
#else
        auto& handler { _handlers[task->get_key()] };
        if (handler) {
            handler(task);
        } else {
            logerror("Task handler for key %lu not presented.", task->get_key());
        }
#endif

        engine::basic_task::destroy(task);
    }

    void work_service::assign_task_handler(basic_task::key_type task_key, task_handler&& handler) noexcept
    {
        _handlers[task_key] = std::move(handler);
    }

}
