/**
 * @file web_loop.cpp
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#include "context/web/web_loop.h"

namespace rocket {

    web_loop::web_loop(task_queue *queue, const task_handler *handler) noexcept :
            work_loop(queue, handler),
            _loop { g_main_loop_new(nullptr, FALSE) }
    {
    }

    // virtual
    web_loop::~web_loop()
    {
        g_main_loop_unref(_loop);
    }

    // virtual
    void web_loop::start() noexcept
    {
        g_idle_add(&web_loop::idle_routine, this);
        g_main_loop_run(_loop);
    }

    // virtual
    void web_loop::stop() noexcept
    {
        g_main_loop_quit(_loop); // @todo Is thread safe?
    }

    gboolean web_loop::on_idle() noexcept
    {
        if (!queue()->empty()) {
            auto task = queue()->dequeue();
            handler()->handle_task(task);
        }
        return TRUE; // @todo Return smart result, depend on state.
    }

    // static
    gboolean web_loop::idle_routine(gpointer pointer) noexcept
    {
        return reinterpret_cast<web_loop *>(pointer)->on_idle(); // @todo Error handling.
    }

}
