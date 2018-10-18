/**
 * @file io_service.cpp
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#include "job/service/session_service.h"
#include "job/service/message/backend_messaging_service.h"
#include "backend_database_message_gen.h"

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
        logdebug("New 'connection_status_changed_task'. Connection id: %llu, status: '%s'.",
                 task->link().connection_id(),
                 engine::connection_status_to_str(task->status()));

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
        if (link.side() == engine::connection_side::remote &&
            link.kind() == engine::connection_kind::slave) {
            auto service { delegate()->service<session_service>() };

            switch (status) {
                case engine::connection_status::connected: {
                    auto session { service->backend_sessions()->create(link) };
                    handshake(session);
                    break;
                }
                case engine::connection_status::disconnected: {
                    service->backend_sessions()->destroy(link);
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }

    void io_service::handshake(backend_session *session) noexcept
    {
        pmp::backend_database::handshake_request_builder builder;
        builder.set_phrase(session->handshake_phrase());
        builder.set_version(0);

        u8 *memory { nullptr };
        size_t length { 0 };
        builder.build(&memory, &length);

        auto task {
                engine::basic_task::create<engine::io_response_task>(session->link(),
                                                                     pmp::backend_database::handshake_request::opcode,
                                                                     memory,
                                                                     length,
                                                                     true)
        };
        router()->enqueue(task);
    }

}
