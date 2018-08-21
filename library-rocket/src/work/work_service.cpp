/**
 * @file execution_service.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "work/work_service.h"

namespace rocket {

    FW_CRUCIAL_BASE_DECLARATION(work_service)

    work_service::work_service(const groot::config_setting::sptr& config,
                               const task_router::sptr& router,
                               const work_context_delegate *service_provider) noexcept :
            _config { config },
            _router { router },
            _context_delegate { service_provider }
    {
        _task_handlers.fill(nullptr);
    }

    void work_service::handle_task(const task::sptr& task) noexcept
    {
        _task_handlers[task->get_key()](task);
    }

    void work_service::add_task_handler(task::key_type task_key, task_handler&& handler) noexcept
    {
        _task_handlers[task_key] = std::move(handler);
    }

}
