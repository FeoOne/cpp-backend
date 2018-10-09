/**
 * @file io_service.cpp
 * @author Feo
 * @date 26/09/2018
 * @brief
 */

#include "job/service/io_service.h"

namespace backend {

    io_service::io_service(const stl::setting& config,
                           engine::task_router *router,
                           const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate)
    {
        EX_ASSIGN_TASK_HANDLER(engine::io_request_task, io_service, handle_io_request_task);
        EX_ASSIGN_TASK_HANDLER(engine::connection_status_changed_task,
                               io_service,
                               handle_connection_status_changed_task);
    }

    // virtual
    void io_service::setup() noexcept
    {

    }

    // virtual
    void io_service::reset() noexcept
    {

    }

    void io_service::handle_connection_status_changed_task(engine::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<engine::connection_status_changed_task *>(base_task) };
        logdebug("New 'connection_status_changed_task'. Connection id: %llu.", task->link().connection_id());
    }

    void io_service::handle_io_request_task(engine::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<engine::io_request_task *>(base_task) };
        logdebug("New 'io_request_task'. Connection id: %llu, opcode: %lu, size: %lu.",
                 task->link().connection_id(),
                 task->opcode(),
                 task->memory_size());

        handle_message(task->opcode(), task->memory(), task->memory_size());
        // todo: free message memory
    }

    // virtual
    void io_service::handle_handshake_request(pmp::backend_database::handshake_request::uptr&& message) noexcept
    {

    }

    // virtual
    void io_service::handle_handshake_response(pmp::backend_database::handshake_response::uptr&& message) noexcept
    {

    }

}
