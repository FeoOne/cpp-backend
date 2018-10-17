//
// Created by Feo on 12/10/2018.
//

#include "job/service/message/database_messaging_service.h"

namespace backend {

    database_messaging_service::database_messaging_service(const stl::setting& config,
                                                           engine::task_router *router,
                                                           const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate)
    {
    }

    // virtual
    void database_messaging_service::setup() noexcept
    {

    }

    // virtual
    void database_messaging_service::reset() noexcept
    {

    }

    // virtual
    void database_messaging_service::handle_handshake_request(
            pmp::backend_database::handshake_request::uptr&& message) noexcept
    {

    }

    // virtual
    void database_messaging_service::handle_handshake_response(
            pmp::backend_database::handshake_response::uptr&& message) noexcept
    {

    }

}
