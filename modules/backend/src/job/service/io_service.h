/**
 * @file io_service.h
 * @author Feo
 * @date 26/09/2018
 * @brief
 */

#ifndef BACKEND_IO_SERVICE_H
#define BACKEND_IO_SERVICE_H

#include <engine.h>

#include "backend_database_message_gen.h"
#include "backend_database_handler_gen.h"

namespace backend {

    class io_service final : public stl::crucial<engine::work_service, io_service>,
                             public pmp::backend_database::message_handler {
    public:
        STL_DECLARE_SMARTPOINTERS(io_service)
        STL_DELETE_ALL_DEFAULT(io_service)

        explicit io_service(const stl::setting& config,
                            engine::task_router *router,
                            const engine::work_service_delegate *delegate) noexcept;

        virtual ~io_service() = default;

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_io_request_task(engine::basic_task *base_task) noexcept;
        void handle_connection_status_changed_task(engine::basic_task *base_task) noexcept;

        void handle_handshake_request(pmp::backend_database::handshake_request::uptr&& message) noexcept final;
        void handle_handshake_response(pmp::backend_database::handshake_response::uptr&& message) noexcept final;

    };

}

#endif /* BACKEND_IO_SERVICE_H */
