/**
 * @file io_service.cpp
 * @author Feo
 * @date 26/09/2018
 * @brief
 */

#include "job/service/session_service.h"
#include "job/service/message/database_messaging_service.h"
#include "job/service/message/manbtc_messaging_service.h"

#include "job/service/io_service.h"

namespace backend {

    io_service::io_service(const stl::setting& config,
                           engine::task_router *router,
                           const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _message_handlers {}
    {
        EX_ASSIGN_TASK_HANDLER(engine::io_request_task, io_service, handle_io_request_task);
        EX_ASSIGN_TASK_HANDLER(engine::connection_status_changed_task,
                               io_service,
                               handle_connection_status_changed_task);
    }

    // virtual
    void io_service::setup() noexcept
    {
        _status_changed_handlers[pmp::session_id::database] =
                std::bind(&io_service::database_status_changed, this, std::placeholders::_1, std::placeholders::_2);

        _message_handlers.push_back(delegate()->service<database_messaging_service>());
        _message_handlers.push_back(delegate()->service<manbtc_messaging_service>());
    }

    // virtual
    void io_service::reset() noexcept
    {
        _message_handlers.clear();
    }

    void io_service::handle_connection_status_changed_task(engine::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<engine::connection_status_changed_task *>(base_task) };
        logdebug("Handle connection_status_changed_task. Connection id: %llu, status: '%s'.",
                task->link().connection_id(),
                 engine::connection_status_to_str(task->status()));

        _status_changed_handlers[task->link().session_id()](task->link(), task->status());
    }

    void io_service::handle_io_request_task(engine::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<engine::io_request_task *>(base_task) };
        logdebug("Handle io_request_task. Connection id: %llu, opcode: %lu, size: %lu.",
                 task->link().connection_id(),
                 task->opcode(),
                 task->memory_size());

        for (auto handler: _message_handlers) {
            if (handler->handle_message(task->opcode(), task->memory(), task->memory_size())) {
                break;
            }
        }
    }

    void io_service::database_status_changed(const engine::connection_link& link,
                                             engine::connection_status status) noexcept
    {
        if (link.side() == engine::connection_side::local &&
            link.kind() == engine::connection_kind::slave) {
            auto service { delegate()->service<session_service>() };

            switch (status) {
                case engine::connection_status::connected: {
                    service->database_sessions()->create(link);
                    break;
                }
                case engine::connection_status::disconnected: {
                    service->database_sessions()->destroy(link);
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }

}
