//
// Created by Feo on 16/08/2018.
//

#include "work/work_context.h"

namespace engine {

    FW_CRUCIAL_BASE_DECLARATION(work_context)

    work_context::work_context(const framework::config_setting::sptr& config,
                               const task_router::sptr& router,
                               const work_loop::sptr& loop) noexcept :
            _config { config },
            _router { router },
            _loop { loop }
    {
        _services.fill(nullptr);
    }

    void work_context::start() noexcept
    {
        _loop->start();
    }

    void work_context::stop() noexcept
    {
        _loop->stop();
    }

    work_service::sptr work_context::get_service(work_service::key_type key) const noexcept
    {
        return _services[key];
    }

    void work_context::add_service(const work_service::sptr& service) noexcept
    {
        _services[service->get_key()] = service;
    }

}
