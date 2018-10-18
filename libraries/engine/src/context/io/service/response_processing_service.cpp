/**
 * @file serialization_service.cpp
 * @author Feo
 * @date 25/09/2018
 * @brief
 */

#include "work/work_service.h"
#include "context/io/task/io_response_task.h"

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
        logdebug("Handle io_response_task. Connection id: %llu, opcode: %lu, size: %lu.",
                 task->link().connection_id(),
                 task->opcode(),
                 task->memory_size());
    }

}
