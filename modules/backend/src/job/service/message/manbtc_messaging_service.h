//
// Created by Feo on 15/10/2018.
//

#ifndef BACKEND_MANBTC_MESSAGING_SERVICE_H
#define BACKEND_MANBTC_MESSAGING_SERVICE_H

#include <engine.h>

#include "backend_manbtc_message_gen.h"
#include "backend_manbtc_handler_gen.h"

namespace backend {

    class manbtc_messaging_service final : public stl::crucial<engine::work_service, manbtc_messaging_service>,
                                           public pmp::backend_manbtc::message_handler {
    public:
        STL_DECLARE_SMARTPOINTERS(manbtc_messaging_service)
        STL_DELETE_ALL_DEFAULT(manbtc_messaging_service)

        explicit manbtc_messaging_service(const stl::setting& config,
                                          engine::task_router *router,
                                          const engine::work_service_delegate *delegate) noexcept;
        virtual ~manbtc_messaging_service() = default;

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_handshake_request(pmp::backend_manbtc::handshake_request::uptr&& message) noexcept final;
        void handle_handshake_response(pmp::backend_manbtc::handshake_response::uptr&& message) noexcept final;

    };

}

#endif /* BACKEND_MANBTC_MESSAGING_SERVICE_H */
