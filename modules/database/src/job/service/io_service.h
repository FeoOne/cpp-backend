/**
 * @file io_service.h
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#ifndef DATABASE_IO_SERVICE_H
#define DATABASE_IO_SERVICE_H

#include <pmp.h>
#include <engine.h>

#include "job/session/backend_session.h"

namespace database {

    class io_service : public stl::crucial<engine::work_service, io_service> {
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
        using status_changed_fn = std::function<void(const engine::connection_link&,
                                                     engine::connection_status,
                                                     engine::connection_status)>;

        std::array<status_changed_fn, pmp::session_id::max_count>   _status_changed_handlers;
        std::vector<pmp::basic_message_handler *>                   _message_handlers;

        void handle_io_request_task(engine::basic_task *base_task) noexcept;
        void handle_connection_status_changed_task(engine::basic_task *base_task) noexcept;

        void backend_status_changed(const engine::connection_link& link,
                                    engine::connection_status status,
                                    engine::connection_status previous_status) noexcept;

        void handshake(backend_session *session) noexcept;

    };

}

#endif /* DATABASE_IO_SERVICE_H */
