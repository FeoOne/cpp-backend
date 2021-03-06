/**
 * @file io_service.h
 * @author Feo
 * @date 26/09/2018
 * @brief
 */

#ifndef BACKEND_IO_SERVICE_H
#define BACKEND_IO_SERVICE_H

#include <pmp.h>
#include <engine.h>

namespace backend {

    class io_service final : public stl::crucial<engine::work_service, io_service> {
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

        void database_status_changed(const engine::connection_link& link,
                                     engine::connection_status status,
                                     engine::connection_status previous_status) noexcept;

    };

}

#endif /* BACKEND_IO_SERVICE_H */
