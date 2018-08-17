//
// Created by Feo on 17/08/2018.
//

#include "web/webserver_loop.h"

namespace engine {

    webserver_loop::webserver_loop()
    {
        int status = uv_loop_init(&_loop);
        logassert(status == 0);

        status = uv_async_init(&_loop, &_wakeup_handle, &webserver_loop::wakeup_routine);
        logassert(status == 0);
        _wakeup_handle.data = this;
    }

    // virtual
    webserver_loop::~webserver_loop()
    {
        int status = uv_loop_close(&_loop);
        logassert(status == 0);
    }

    void webserver_loop::start() noexcept
    {
        int status = uv_run(&_loop, UV_RUN_DEFAULT);
        lognotice("Loop stopped with %d active handlers.", status);
    }

    void webserver_loop::stop() noexcept
    {
        uv_stop(&_loop);
    }

    void webserver_loop::on_new_task() noexcept
    {
        int status = uv_async_send(&_wakeup_handle);
        logassert(status == 0);
    }

    void webserver_loop::on_wakeup() noexcept
    {
        // @todo Process task queue
    }

    // static
    void webserver_loop::wakeup_routine(uv_async_t *async_handle) noexcept
    {
        reinterpret_cast<webserver_loop *>(async_handle->data)->on_wakeup();
    }

}
