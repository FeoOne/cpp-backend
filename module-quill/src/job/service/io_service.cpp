/**
 * @file io_service.cpp
 * @author Feo
 * @date 26/09/2018
 * @brief
 */

#include "job/service/io_service.h"

namespace quill {

    io_service::io_service(const groot::setting& config,
                           rocket::task_router *router,
                           const rocket::work_service_delegate *service_delegate) noexcept :
            crucial(config, router, service_delegate)
    {
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

    void io_service::handle_message_request_task(rocket::basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<rocket::message_request_task *>(base_task) };

        rocket::basic_task::destroy(task);
    }

}
