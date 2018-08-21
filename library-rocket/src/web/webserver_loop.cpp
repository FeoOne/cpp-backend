/**
 * @file webserver_loop.cpp
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#include "web/webserver_loop.h"

namespace rocket {

    webserver_loop::webserver_loop(const task_queue::sptr& queue, task_handler *handler) noexcept :
            work_loop(queue, handler),
            _loop { g_main_loop_new(nullptr, FALSE) }
    {
    }

    // virtual
    webserver_loop::~webserver_loop()
    {
        g_main_loop_unref(_loop);
    }

    // virtual
    void webserver_loop::start() noexcept
    {
        g_idle_add(&webserver_loop::idle_routine, this);
        g_main_loop_run(_loop);
    }

    // virtual
    void webserver_loop::stop() noexcept
    {
        g_main_loop_quit(_loop); // @todo Is thread safe?
    }

    gboolean webserver_loop::on_idle() noexcept
    {
        if (!get_queue()->empty()) {
            auto task = get_queue()->dequeue();
            get_task_handler()->handle_task(task);
        }
    }

    // static
    gboolean webserver_loop::idle_routine(gpointer pointer) noexcept
    {
        return reinterpret_cast<webserver_loop *>(pointer)->on_idle(); // @todo Error handling.
    }

}
