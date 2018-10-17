//
// Created by Feo on 12/10/2018.
//

#ifndef BACKEND_DATABASE_MESSAGING_SERVICE_H
#define BACKEND_DATABASE_MESSAGING_SERVICE_H

#include <engine.h>

#include "backend_database_message_gen.h"
#include "backend_database_handler_gen.h"

namespace backend {

    class database_messaging_service final : public stl::crucial<engine::work_service, database_messaging_service>,
                                             public pmp::backend_database::message_handler {
    public:
        STL_DECLARE_SMARTPOINTERS(database_messaging_service)
        STL_DELETE_ALL_DEFAULT(database_messaging_service)

        explicit database_messaging_service(const stl::setting& config,
                                            engine::task_router *router,
                                            const engine::work_service_delegate *delegate) noexcept;
        virtual ~database_messaging_service() = default;

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_handshake_request(pmp::backend_database::handshake_request::uptr&& message) noexcept final;
        void handle_handshake_response(pmp::backend_database::handshake_response::uptr&& message) noexcept final;

    };

}

#endif /* BACKEND_DATABASE_MESSAGING_SERVICE_H */
