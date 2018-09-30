/**
 * @file request_processing_service.h
 * @author Feo
 * @date 25/09/2018
 * @brief
 */

#ifndef ENGINE_REQUEST_PROCESSING_SERVICE_H
#define ENGINE_REQUEST_PROCESSING_SERVICE_H

#include "work/work_service.h"
#include "context/io/connection/tcp_connection.h"

namespace engine {

    class request_processing_service : public stl::crucial<work_service, request_processing_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(request_processing_service)
        STL_DELETE_ALL_DEFAULT(request_processing_service)

        explicit request_processing_service(const stl::setting& config,
                                            task_router *router,
                                            const work_service_delegate *delegate) noexcept;
        virtual ~request_processing_service();

        void setup() noexcept final;
        void reset() noexcept final;

        void process_input(tcp_connection *connection) noexcept;

    private:

    };

}

#endif /* ENGINE_REQUEST_PROCESSING_SERVICE_H */
