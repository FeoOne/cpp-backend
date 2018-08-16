/**
 * @file web_server_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "events/events.h"

#include "web/web_server_loop.h"

namespace engine {

    web_server_loop::web_server_loop(const event_queue::sptr& queue) noexcept :
            work_loop(queue),
            _loop { g_main_loop_new(nullptr, FALSE) },
            _should_work { false }
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
            _should_work = true;

            g_idle_add(&web_server_loop::on_idle, this);
            g_main_loop_run(_loop);
        } else {
            logcrit("Failed to start web server loop.");
        }
    }

    // virtual
    void web_server_loop::stop() noexcept
    {
        if (_loop != nullptr) {
            _should_work = false;

            g_main_loop_quit(_loop);
        }
    }

    // virtual
    bool web_server_loop::stopped() const noexcept
    {
        return (g_main_loop_is_running(_loop) == FALSE);
    }

    gboolean web_server_loop::on_idle() noexcept
    {
        auto eve = get_queue()->dequeue();
        if (eve != nullptr) {
            logdebug("Dequeued event with key: %lu, name: '%s'.",
                     eve->get_key(),
                     event_name_from_key(eve->get_key()).data());
            handle_event(eve);
        }

        return _should_work ? TRUE : FALSE;
    }

    // static
    gboolean web_server_loop::on_idle(gpointer pointer) noexcept
    {
        // @todo Error handling
        return reinterpret_cast<web_server_loop *>(pointer)->on_idle();
    }

}
