/**
 * @file io_service.h
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#ifndef STRANGE_IO_SERVICE_H
#define STRANGE_IO_SERVICE_H

#include <rocket.h>

namespace strange {

    class io_service : public groot::crucial<rocket::work_service, io_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(io_service)
        GR_DELETE_ALL_DEFAULT(io_service)

        explicit io_service(const groot::setting& config,
                            rocket::task_router *router,
                            const rocket::work_service_delegate *delegate) noexcept;
        virtual ~io_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:

        void handle_message_request_task(rocket::basic_task *base_task) noexcept;
        void handle_connection_status_changed_task(rocket::basic_task *base_task) noexcept;

    };

}

#endif /* STRANGE_IO_SERVICE_H */
