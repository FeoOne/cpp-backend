/**
 * @file backend_messaging_service.h
 * @author Feo
 * @date 17/10/2018
 * @brief
 */

#ifndef DATABASE_BACKEND_MESSAGING_SERVICE_H
#define DATABASE_BACKEND_MESSAGING_SERVICE_H

#include <pmp.h>
#include <engine.h>

#include "backend_database_message_gen.h"
#include "backend_database_handler_gen.h"

namespace database {

    class backend_messaging_service : public stl::crucial<engine::work_service, backend_messaging_service>,
                                      public pmp::backend_database::message_handler {
    public:
        explicit backend_messaging_service(const stl::setting& config,
                                           engine::task_router *router,
                                           const engine::work_service_delegate *delegate) noexcept;
        virtual ~backend_messaging_service() = default;

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_handshake_request(pmp::backend_database::handshake_request::uptr&& message) noexcept final;
        void handle_handshake_response(pmp::backend_database::handshake_response::uptr&& message) noexcept final;

    };

}

#endif /* DATABASE_BACKEND_MESSAGING_SERVICE_H */
