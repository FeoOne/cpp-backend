/**
 * @file response_processing_service.h
 * @author Feo
 * @date 25/09/2018
 * @brief
 */

#ifndef ROCKET_RESPONSE_PROCESSING_SERVICE_H
#define ROCKET_RESPONSE_PROCESSING_SERVICE_H

#include "work/work_service.h"

namespace rocket {

    class response_processing_service : public groot::crucial<work_service, response_processing_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(response_processing_service)
        GR_DELETE_ALL_DEFAULT(response_processing_service)

        explicit response_processing_service(const groot::setting& config,
                                             task_router *router,
                                             const work_service_delegate *delegate) noexcept;
        virtual ~response_processing_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:

    };

}

#endif /* ROCKET_RESPONSE_PROCESSING_SERVICE_H */
