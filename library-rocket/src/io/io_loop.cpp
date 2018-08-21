/**
 * @file io_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "io/io_loop.h"

namespace rocket {

    io_loop::io_loop(const task_queue::sptr& queue, task_handler *handler) noexcept :
            work_loop(queue, handler)
    {
        uv_loop_init(&_loop);
    }

    // virtual
    io_loop::~io_loop()
    {
        uv_loop_close(&_loop);
    }

    // virtual
    void io_loop::start() noexcept
    {
        int status = uv_async_init(&_loop, &_async_handle, &io_loop::async_routine);
        logassert(status == 0);
        _async_handle.data = this;

        status = uv_run(&_loop, UV_RUN_DEFAULT);
        lognotice("Loop stopped with %d pending handles.", status);
    }

    // virtual
    void io_loop::stop() noexcept
    {
        uv_stop(&_loop);
    }

    void io_loop::on_async() noexcept
    {
        while (!get_queue()->empty()) {
            auto task = get_queue()->dequeue();
            // @todo Handle task.
        }
    }

    // static
    void io_loop::async_routine(uv_async_t *handle) noexcept
    {
        logassert(handle != nullptr);
        logassert(handle->data != nullptr);
        static_cast<io_loop *>(handle->data)->on_async();
    }

}
