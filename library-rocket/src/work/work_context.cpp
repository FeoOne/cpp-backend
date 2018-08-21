//
// Created by Feo on 16/08/2018.
//

#include "work/work_context.h"

namespace rocket {

    FW_CRUCIAL_BASE_DECLARATION(work_context)

    work_context::work_context(const groot::config_setting::sptr& config,
                               const task_router::sptr& router,
                               const work_loop::sptr& loop) noexcept :
            _config { config },
            _router { router },
            _loop { loop }
    {
        _services.fill(nullptr);
        _handler_keys.fill(std::numeric_limits<task::key_type>::max());
    }

    void work_context::start() noexcept
    {
        _loop->start();
    }

    void work_context::stop() noexcept
    {
        _loop->stop();
    }

    void work_context::handle_task(const task::sptr& task) noexcept
    {
        _services[_handler_keys[task->get_key()]]->handle_task(task);
    }

    work_service::sptr work_context::get_service(work_service::key_type key) const noexcept
    {
        return _services[key];
    }

    void work_context::add_service(const work_service::sptr& service) noexcept
    {
        _services[service->get_key()] = service;
    }

    void work_context::register_task_handler(task::key_type task_key,
                                             work_service::key_type service_key) noexcept
    {
        _handler_keys[task_key] = service_key;
    }

}
