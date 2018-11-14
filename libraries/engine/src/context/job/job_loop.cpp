/**
 * @file job_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "task/queue/quiet_task_queue.h"

#include "context/job/job_loop.h"

namespace engine {

    job_loop::job_loop(task_queue *queue, const task_handler *handler) noexcept :
            work_loop(queue, handler)
    {
        uv_loop_init(&_loop);
    }

    // virtual
    job_loop::~job_loop()
    {
        uv_loop_close(&_loop);
    }

    // virtual
    void job_loop::start() noexcept
    {
        reinterpret_cast<quiet_task_queue *>(queue())->set_notify_fn(std::bind(&job_loop::notify, this));

        int status = uv_async_init(&_loop, &_async_handle, &job_loop::async_callback);
        logassert(status == 0, "Invalid status.");
        _async_handle.data = this;

        status = uv_run(&_loop, UV_RUN_DEFAULT);
        lognotice("Loop stopped with %d pending handles.", status);
    }

    // virtual
    void job_loop::stop() noexcept
    {
        uv_stop(&_loop);

        reinterpret_cast<quiet_task_queue *>(queue())->set_notify_fn(nullptr);
    }

    void job_loop::notify() noexcept
    {
        uv_async_send(&_async_handle);
    }

    void job_loop::on_async() noexcept
    {
        while (!queue()->empty()) {
            auto task = queue()->dequeue();
            handler()->handle_task(task);
        }
    }

    // static
    void job_loop::async_callback(uv_async_t *handle) noexcept
    {
        logassert(handle != nullptr, "Invalid handle.");
        logassert(handle->data != nullptr, "Invalid data.");
        static_cast<job_loop *>(handle->data)->on_async();
    }

}
