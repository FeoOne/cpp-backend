/**
 * @file io_service.cpp
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#include "job/service/io_service.h"

namespace strange {

    io_service::io_service(const groot::setting& config,
                           rocket::task_router *router,
                           const rocket::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate)
    {
        RC_ASSIGN_TASK_HANDLER(rocket::io_request_task, io_service, handle_io_request_task);
        RC_ASSIGN_TASK_HANDLER(rocket::connection_status_changed_task,
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

    }

    // virtual
    void io_service::reset() noexcept
    {

    }

    void io_service::handle_connection_status_changed_task(rocket::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<rocket::connection_status_changed_task *>(base_task) };
        logdebug("New 'connection_status_changed_task'. Connection id: %llu.", task->link().connection_id());
    }

    void io_service::handle_io_request_task(rocket::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<rocket::io_request_task *>(base_task) };
        logdebug("New io_request_task. Connection id: %llu, opcode: %lu, length: %lu.",
                 task->link().connection_id(),
                 task->opcode(),
                 task->length());
    }

}

