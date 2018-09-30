/**
 * @file webserver_service.h
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#ifndef ROCKET_WEBSERVER_SERVICE_H
#define ROCKET_WEBSERVER_SERVICE_H

#include <libsoup/soup.h>

#include "work/work_service.h"

namespace rocket {

    class webserver_service final : public groot::crucial<work_service, webserver_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(webserver_service)
        GR_DELETE_ALL_DEFAULT(webserver_service)

        explicit webserver_service(const groot::setting& config,
                                   task_router *router,
                                   const work_service_delegate *delegate) noexcept;
        virtual ~webserver_service();

        void setup() noexcept final;
        void reset() noexcept final;

        SoupServer *get_server() noexcept { return _server; }

    private:
        SoupServer *            _server;

        void print_server_info() const noexcept;

    };

}

#endif /* ROCKET_WEBSERVER_SERVICE_H */
