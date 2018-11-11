/**
 * @file request_processing_service.cpp
 * @author Feo
 * @date 25/09/2018
 * @brief
 */

#include "message/message.h"
#include "context/io/service/tcp_service.h"
#include "context/io/task/io_request_task.h"

#include "context/io/service/request_processing_service.h"

namespace engine {

    request_processing_service::request_processing_service(const stl::setting &config,
                                                     task_router *router,
                                                     const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate)
    {
    }

    // virtual
    request_processing_service::~request_processing_service()
    {
    }

    void request_processing_service::setup() noexcept
    {

    }

    void request_processing_service::reset() noexcept
    {

    }

    void request_processing_service::process_input(tcp_connection *connection) noexcept
    {
        auto read_stream { connection->read_stream() };
        if (read_stream->useful_size() < message_header::size) {
            // data size insufficient to read header
            return;
        }

        // validate magic number
        message_header header { read_stream->head() };
        if (!header.is_magic_correct()) {
            logerror("Magic number mismatch (0x%x) for connection 0x%llx.", header.magic(), connection);
            delegate()->service<tcp_service>()->shutdown_connection(connection);
            return;
        }

        if (header.length() != 0 && read_stream->useful_size() < message_header::size + header.length()) {
            // data size insufficient to read message
            return;
        }

        read_stream->increase_head(message_header::size);

        // validate checksum
        if (header.crc32() != stl::checksum::crc32(read_stream->head(), header.length())) {
            logerror("CRC32 checksum mismatch for connection 0x%llx.", connection);
            delegate()->service<tcp_service>()->shutdown_connection(connection);
            return;
        }

        u8 *memory {  nullptr };
        size_t size { 0 };

        // grab message body if presented
        if (header.length() != 0) {
            memory = read_stream->head();
            size = header.length();

            read_stream->increase_head(header.length());
        }

        read_stream->flush_if_needed();

        auto task { basic_task::create<io_request_task>(connection->link(), header.opcode(), memory, size) };
        router()->enqueue(task);
    }

}
