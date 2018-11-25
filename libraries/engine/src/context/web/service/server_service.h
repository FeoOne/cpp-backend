/**
 * @file server_service.h
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#ifndef ENGINE_WEBSERVER_SERVICE_H
#define ENGINE_WEBSERVER_SERVICE_H

#include <libsoup/soup.h>

#include "work/service/work_service.h"

namespace engine {

    class server_service final : public stl::crucial<work_service, server_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(server_service)
        STL_DELETE_ALL_DEFAULT(server_service)

        explicit server_service(const stl::setting& config,
                                task_router *router,
                                const work_service_delegate *delegate) noexcept;
        virtual ~server_service();

        void setup() noexcept final;
        void reset() noexcept final;

        SoupServer *soup_server() noexcept { return _soup_server; }

    private:
        SoupServer *            _soup_server;

        void print_server_info() const noexcept;

    };

}

#endif /* ENGINE_WEBSERVER_SERVICE_H */
