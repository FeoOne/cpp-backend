/**
 * @file request_processing_service.h
 * @author Feo
 * @date 25/09/2018
 * @brief
 */

#ifndef ROCKET_REQUEST_PROCESSING_SERVICE_H
#define ROCKET_REQUEST_PROCESSING_SERVICE_H

#include "work/work_service.h"
#include "context/io/connection/tcp_connection.h"

namespace rocket {

    class request_processing_service : public groot::crucial<work_service, request_processing_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(request_processing_service)
        GR_DELETE_ALL_DEFAULT(request_processing_service)

        explicit request_processing_service(const groot::setting& config,
                                            task_router *router,
                                            const work_service_delegate *delegate) noexcept;
        virtual ~request_processing_service();

        void setup() noexcept final;
        void reset() noexcept final;

        void process_input(tcp_connection *connection) noexcept;

    private:

    };

}

#endif /* ROCKET_REQUEST_PROCESSING_SERVICE_H */
