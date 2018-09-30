/**
 * @file response_processing_service.h
 * @author Feo
 * @date 25/09/2018
 * @brief
 */

#ifndef ENGINE_RESPONSE_PROCESSING_SERVICE_H
#define ENGINE_RESPONSE_PROCESSING_SERVICE_H

#include "work/work_service.h"

namespace engine {

    class response_processing_service : public stl::crucial<work_service, response_processing_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(response_processing_service)
        STL_DELETE_ALL_DEFAULT(response_processing_service)

        explicit response_processing_service(const stl::setting& config,
                                             task_router *router,
                                             const work_service_delegate *delegate) noexcept;
        virtual ~response_processing_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:

    };

}

#endif /* ENGINE_RESPONSE_PROCESSING_SERVICE_H */
