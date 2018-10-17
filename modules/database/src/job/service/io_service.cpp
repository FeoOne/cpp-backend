/**
 * @file io_service.cpp
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#include "job/service/io_service.h"

namespace database {

    io_service::io_service(const stl::setting& config,
                           engine::task_router *router,
                           const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _status_changed_handlers {}
    {
        _status_changed_handlers.fill(nullptr);

        EX_ASSIGN_TASK_HANDLER(engine::io_request_task, io_service, handle_io_request_task);
        EX_ASSIGN_TASK_HANDLER(engine::connection_status_changed_task,
                               io_service,
                               handle_connection_status_changed_task);
    }

    // virtual
    io_service::~io_service()
    {

    }

    // virtual
    void io_service::setup() noexcept
    {
        _status_changed_handlers[pmp::session_id::backend] =
                std::bind(&io_service::backend_status_changed, this, std::placeholders::_1, std::placeholders::_2);
    }

    // virtual
    void io_service::reset() noexcept
    {

    }

    void io_service::handle_connection_status_changed_task(engine::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<engine::connection_status_changed_task *>(base_task) };
        logdebug("New 'connection_status_changed_task'. Connection id: %llu.", task->link().connection_id());

        _status_changed_handlers[task->link().session_id()](task->link(), task->status());
    }

    void io_service::handle_io_request_task(engine::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<engine::io_request_task *>(base_task) };
        logdebug("New io_request_task. Connection id: %llu, opcode: %lu, length: %lu.",
                 task->link().connection_id(),
                 task->opcode(),
                 task->memory_size());
    }

    void io_service::backend_status_changed(const engine::connection_link& link,
                                            engine::connection_status status) noexcept
    {

    }

}
