/**
 * @file execution_service.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "work/work_service.h"

namespace rocket {

    GR_CRUCIAL_BASE_DECLARATION(work_service)

    work_service::work_service(const groot::config_setting::sptr& config,
                               const task_router::sptr& router,
                               const work_service_delegate *delegate) noexcept :
            _config { config },
            _router { router },
            _delegate { delegate }
    {
        _handlers.fill(nullptr);
    }

    void work_service::handle_task(const task::sptr& task) noexcept
    {
        _handlers[task->get_key()](task);
    }

    void work_service::assign_task_handler(task::key_type task_key, handler&& handler) noexcept
    {
        _handlers[task_key] = std::move(handler);
    }

}
