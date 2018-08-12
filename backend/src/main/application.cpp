/**
 * @file application.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include "main/application.h"

namespace backend {

    using namespace engine;

    application::application() :
            _web_server_controller { nullptr }
    {

    }

    application::~application()
    {

    }

    void application::_before_run() noexcept
    {
//        auto context = _get_contexts(engine_const::SYSTEM_CONTEXT_NAME)[0];
//        _web_server_controller = web_server_controller::make_unique(context->get_service<http_handle_service>());
//        _web_server_controller->create();
    }

    void application::_after_run() noexcept
    {
//        _web_server_controller->destroy();
    }

}
