/**
 * @file session_service.cpp
 * @author Feo
 * @date 18/10/2018
 * @brief
 */

#include "job/service/session_service.h"

namespace database {

    session_service::session_service(const stl::setting& config,
                                     engine::task_router *router,
                                     const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _backend_sessions { engine::session_manager<backend_session>::make_unique() }
    {

    }

    // virtual
    void session_service::setup() noexcept
    {

    }

    // virtual
    void session_service::reset() noexcept
    {

    }

}
