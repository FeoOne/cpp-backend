/**
 * @file request_service.h
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#ifndef ROCKET_REQUEST_SERVICE_H
#define ROCKET_REQUEST_SERVICE_H

#include "work/work_service.h"

namespace rocket {

    class request_service final : public groot::crucial<work_service, request_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(request_service)
        GR_DELETE_ALL_DEFAULT(request_service)

        explicit request_service(const groot::config_setting::sptr& config,
                              const task_router::sptr& router,
                              const work_context_delegate *service_provider) noexcept;
        virtual ~request_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_db_request_task(const task::sptr& t) noexcept;

    };

}

#endif /* PROJECT_REQUEST_SERVICE_H */
