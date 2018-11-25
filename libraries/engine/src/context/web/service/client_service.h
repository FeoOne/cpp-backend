/**
 * @file client_service.h
 * @author Feo
 * @date 26/11/2018
 * @brief
 */

#ifndef ENGINE_CLIENT_SERVICE_H
#define ENGINE_CLIENT_SERVICE_H

#include <libsoup/soup.h>

#include "work/service/work_service.h"

namespace engine {

    class client_service final : public stl::crucial<work_service, client_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(client_service)
        STL_DELETE_ALL_DEFAULT(client_service)

        explicit client_service(const stl::setting& config,
                                task_router *router,
                                const work_service_delegate *delegate) noexcept;
        virtual ~client_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        SoupSession *           _soup_session;

    };

}

#endif /* ENGINE_CLIENT_SERVICE_H */
