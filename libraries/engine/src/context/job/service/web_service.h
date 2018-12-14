//
// Created by Feo on 14/12/2018.
//

#ifndef ENGINE_WEB_SERVICE_H
#define ENGINE_WEB_SERVICE_H

#include "work/service/work_service.h"

namespace engine {

    class web_service final : public stl::crucial<work_service, web_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(web_service)
        STL_DELETE_ALL_DEFAULT(web_service)

        explicit web_service(const stl::setting& config,
                             task_router *router,
                             const work_service_delegate *delegate) noexcept;

        virtual ~web_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_http_client_response_task(engine::basic_task *base_task) noexcept;

    };

}

#endif /* ENGINE_WEB_SERVICE_H */
