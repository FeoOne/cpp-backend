//
// Created by Feo on 16/08/2018.
//

#include "work/work_context.h"

namespace rocket {

    GR_CRUCIAL_BASE_DECLARATION(work_context)

    work_context::work_context(const groot::setting& config,
                               task_router *router,
                               work_loop::uptr&& loop) noexcept :
            _loop { std::move(loop) },
            _config { config },
            _router { router },
            _services {},
            _handler_bindings {}
    {
        _handler_bindings.fill(GR_CRUCIAL_KEY_UNDEFINED);
    }

    void work_context::start() noexcept
    {
        _loop->start();
    }

    void work_context::stop() noexcept
    {
        _loop->stop();
    }

    void work_context::setup_services() noexcept
    {
        for (auto& service: _services) {
            if (service) {
                service->setup();
            }
        }
    }

    void work_context::reset_services() noexcept
    {
        for (auto& service: _services) {
            if (service) {
                service->reset();
            }
        }
    }

    void work_context::handle_task(basic_task *task) const noexcept
    {
#ifdef NDEBUG
        _services[_handler_bindings[task->get_key()]]->handle_task(task);
#else
        auto service { _services[_handler_bindings[task->get_key()]].get() };
        if (service != nullptr) {
            service->handle_task(task);
        } else {
            logerror("Service for task key %lu not presented.", task->get_key());
        }
#endif
    }

    void work_context::bind_task_route(basic_task::key_type task_key, work_service::key_type service_key) noexcept
    {
        _handler_bindings[task_key] = service_key;
    }

    void work_context::add_service(work_service::uptr&& service) noexcept
    {
        _services[service->get_key()] = std::move(service);
    }

    work_loop *work_context::get_loop_impl() const noexcept
    {
        return _loop.get();
    }

    work_service *work_context::get_service_impl(work_service::key_type key) const noexcept
    {
        return _services[key].get();
    }

}
