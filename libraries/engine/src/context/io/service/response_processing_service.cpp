/**
 * @file serialization_service.cpp
 * @author Feo
 * @date 25/09/2018
 * @brief
 */

#include "message/message.h"
#include "work/service/work_service.h"
#include "context/io/service/io_connection_service.h"

#include "context/io/service/response_processing_service.h"

namespace engine {

    response_processing_service::response_processing_service(const stl::setting &config,
                                                 task_router *router,
                                                 const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate)
    {
        EX_ASSIGN_TASK_HANDLER(io_response_task, response_processing_service, handle_io_response_task);
    }

    // virtual
    response_processing_service::~response_processing_service()
    {
    }

    void response_processing_service::setup() noexcept
    {

    }

    void response_processing_service::reset() noexcept
    {

    }

    void response_processing_service::handle_io_response_task(engine::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<io_response_task *>(base_task) };
        logdebug("Handle io_response_task. Connection id: %llu, opcode: %u, size: %u.",
                 task->link().connection_id(),
                 task->opcode(),
                 task->length());

        switch (task->link().protocol()) {
            case socket_type::stream: {
                handle_tcp_response(task);
                break;
            }
            case socket_type::datagram: {

                break;
            }
            default: {
                break;
            }
        }
    }

    void response_processing_service::handle_tcp_response(io_response_task *task) noexcept
    {
        auto manager { delegate()->service<io_connection_service>()->manager<tcp_connection>() };
        auto connection { manager->get(task->link()) };
        auto stream { connection->write_stream() };

        stream->grow_if_needed();

        message_header header { stream->tail() };
        header.magic(message_header::magic_number);
        header.opcode(task->opcode());
        header.length(static_cast<u32>(task->length()));

        u32 crc { 0 };
        if (task->length() != 0) {
            crc = stl::checksum::crc32(task->memory(), task->length());
        }
        header.crc32(crc);

        stream->increase_tail(message_header::size);

        if (task->length() != 0) {
            std::memcpy(stream->tail(), task->memory(), task->length());
            stream->increase_tail(task->length());
        }

        if (task->is_urgent()) {
            connection->write();
        }
    }

}
