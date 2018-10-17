/**
 * @file backend_messaging_service.cpp
 * @author Feo
 * @date 17/10/2018
 * @brief
 */

#include "job/service/message/backend_messaging_service.h"

namespace database {

    backend_messaging_service::backend_messaging_service(const stl::setting& config,
                                                         engine::task_router *router,
                                                         const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate)
    {
    }

    // virtual
    void backend_messaging_service::setup() noexcept
    {

    }

    // virtual
    void backend_messaging_service::reset() noexcept
    {

    }

    // virtual
    void backend_messaging_service::handle_handshake_request(
            pmp::backend_database::handshake_request::uptr&& message) noexcept
    {

    }

    // virtual
    void backend_messaging_service::handle_handshake_response(
            pmp::backend_database::handshake_response::uptr&& message) noexcept
    {

    }

}
