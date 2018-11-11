/**
 * @file io_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "task/queue/quiet_task_queue.h"

#include "context/io/io_loop.h"

namespace engine {

    io_loop::io_loop(task_queue *queue, const task_handler *handler) noexcept :
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
        reinterpret_cast<quiet_task_queue *>(queue())->set_notify_fn(std::bind(&io_loop::notify, this));

        int status = uv_async_init(&_loop, &_async_handle, &io_loop::async_callback);
        logassert(status == 0, "Invalid status.");
        _async_handle.data = this;

        status = uv_run(&_loop, UV_RUN_DEFAULT);
        lognotice("Loop stopped with %d pending handles.", status);
    }

    // virtual
    void io_loop::stop() noexcept
    {
        uv_stop(&_loop);

        reinterpret_cast<quiet_task_queue *>(queue())->set_notify_fn(nullptr);
    }

    void io_loop::notify() noexcept
    {
        uv_async_send(&_async_handle);
    }

    void io_loop::on_async() noexcept
    {
        while (!queue()->empty()) {
            auto task = queue()->dequeue();
            handler()->handle_task(task);
        }
    }

    // static
    void io_loop::async_callback(uv_async_t *handle) noexcept
    {
        logassert(handle != nullptr, "Invalid handle.");
        logassert(handle->data != nullptr, "Invalid data.");
        static_cast<io_loop *>(handle->data)->on_async();
    }

}
