/**
 * @file web_server_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "web/web_server_loop.h"

namespace engine {

    web_server_loop::web_server_loop() :
            _loop { g_main_loop_new(nullptr, FALSE) }
    {

    }

    // virtual
    web_server_loop::~web_server_loop()
    {
        if (_loop != nullptr) {
            g_main_loop_unref(_loop);
        }
    }

    // virtual
    void web_server_loop::run() noexcept
    {
        if (_loop != nullptr) {
            g_main_loop_run(_loop);
        } else {
            logcrit("Failed to start web server loop.");
        }
    }

    // virtual
    void web_server_loop::stop() noexcept
    {
        if (_loop != nullptr) {
            g_main_loop_quit(_loop);
        }
    }

    // virtual
    bool web_server_loop::stopped() const noexcept
    {
        return (g_main_loop_is_running(_loop) == FALSE);
    }

}
