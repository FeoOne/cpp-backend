//
// Created by Feo on 15/10/2018.
//

#include "job/service/message/manbtc_messaging_service.h"

namespace backend {

    manbtc_messaging_service::manbtc_messaging_service(const stl::setting& config,
                                                       engine::task_router *router,
                                                       const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate)
    {
    }

    // virtual
    void manbtc_messaging_service::setup() noexcept
    {

    }

    // virtual
    void manbtc_messaging_service::reset() noexcept
    {

    }

    // virtual
    void manbtc_messaging_service::handle_handshake_request(const engine::connection_link& link,
            pmp::backend_manbtc::handshake_request::uptr&& message) noexcept
    {

    }

    // virtual
    void manbtc_messaging_service::handle_handshake_response(const engine::connection_link& link,
            pmp::backend_manbtc::handshake_response::uptr&& message) noexcept
    {

    }

}
