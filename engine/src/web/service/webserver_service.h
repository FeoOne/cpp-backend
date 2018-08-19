/**
 * @file webserver_service.h
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#ifndef ENGINE_WEBSERVER_SERVICE_H
#define ENGINE_WEBSERVER_SERVICE_H

#include <libsoup/soup.h>

#include "work/work_service.h"

namespace engine {

    class webserver_service final : public framework::crucial<work_service, webserver_service> {
    public:
        FW_DECLARE_SMARTPOINTERS(webserver_service)
        FW_DELETE_ALL_DEFAULT(webserver_service)

        explicit webserver_service(const framework::config_setting::sptr& config,
                                   const task_router::sptr& router,
                                   const work_service_provider *service_provider) noexcept;
        virtual ~webserver_service();

        void setup() noexcept final;
        void reset() noexcept final;

        void handle_task(const task::sptr& task) noexcept final;

        SoupServer *get_server() noexcept { return _server; }

    private:
        SoupServer *            _server;

        void print_server_info() const noexcept;

    };

}

#endif /* ENGINE_WEBSERVER_SERVICE_H */
