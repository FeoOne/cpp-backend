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

        web_server_controller();
        ~web_server_controller();

        void create() noexcept;
        void destroy() noexcept;

    private:

    };

}

#endif /* BACKEND_WEB_SERVER_CONTROLLER_H */
