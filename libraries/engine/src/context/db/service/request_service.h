/**
 * @file request_service.h
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#ifndef ENGINE_REQUEST_SERVICE_H
#define ENGINE_REQUEST_SERVICE_H

#include "work/work_service.h"

namespace engine {

    class request_service final : public stl::crucial<work_service, request_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(request_service)
        STL_DELETE_ALL_DEFAULT(request_service)

        explicit request_service(const stl::setting& config,
                                 task_router *router,
                                 const work_service_delegate *delegate) noexcept;
        virtual ~request_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_db_request_task(basic_task *task) noexcept;

    };

}

#endif /* PROJECT_REQUEST_SERVICE_H */
