/**
 * @file application.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include "main/application.h"

namespace backend {

    void application::_before_run() noexcept
    {
        _web_server_controller->create();
    }

    void application::_after_run() noexcept
    {
        _web_server_controller->destroy();
    }

}
