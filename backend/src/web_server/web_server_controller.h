/**
 * @file web_server_controller.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef BACKEND_WEB_SERVER_CONTROLLER_H
#define BACKEND_WEB_SERVER_CONTROLLER_H

#include <engine.h>

namespace backend {

    class web_server_controller {
    public:
        FW_DECLARE_SMARTPOINTERS(web_server_controller)
        FW_DELETE_ALL_DEFAULT(web_server_controller)

        explicit web_server_controller(const engine::http_handle_service::sptr& http_service) noexcept;
        ~web_server_controller();

        void create() noexcept;
        void destroy() noexcept;

    private:
        engine::http_handle_service::sptr       _http_service;

    };

}

#endif /* BACKEND_WEB_SERVER_CONTROLLER_H */
