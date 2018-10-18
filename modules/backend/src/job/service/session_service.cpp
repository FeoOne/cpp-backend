/**
 * @file session_service.cpp
 * @author Feo
 * @date 18/10/2018
 * @brief
 */

#include "job/service/session_service.h"

namespace backend {

    session_service::session_service(const stl::setting& config,
                                     engine::task_router *router,
                                     const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _database_sessions { database_session_manager::make_unique() }
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
