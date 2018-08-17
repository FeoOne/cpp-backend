/**
 * @file webserver_context.cpp
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#include "web/webserver_loop.h"

#include "web/webserver_context.h"

namespace engine {

    webserver_context::webserver_context(const framework::config_setting::sptr& config,
                                         const task_router::sptr& router) noexcept :
            crucial(config, router, webserver_loop::make_unique())
    {
    }

}
