/**
 * @file application.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef BACKEND_APPLICATION_H
#define BACKEND_APPLICATION_H

#include <engine.h>

#include "web_server/web_server_controller.h"

namespace backend {

    class application : public engine::application {
    public:
        FW_DECLARE_SMARTPOINTERS(application)

        application();
        virtual ~application();

    private:
        web_server_controller::uptr     _web_server_controller;

        void _before_run() noexcept final;
        void _after_run() noexcept final;

    };

}

#endif /* BACKEND_APPLICATION_H */
