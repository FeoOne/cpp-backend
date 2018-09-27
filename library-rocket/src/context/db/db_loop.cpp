/**
 * @file db_loop.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "context/db/db_loop.h"

namespace rocket {

    db_loop::db_loop(task_queue *queue, const task_handler *handler) noexcept :
            work_loop(queue, handler)
    {
        uv_loop_init(&_loop);
    }

    // virtual
    db_loop::~db_loop()
    {
        uv_loop_close(&_loop);
    }

    // virtual
    void db_loop::start() noexcept
    {
        int status = uv_async_init(&_loop, &_async_handle, &db_loop::async_routine);
        logassert(status == 0, "Invalid status");
        _async_handle.data = this;

        status = uv_run(&_loop, UV_RUN_DEFAULT);
        lognotice("Loop stopped with %d pending handles.", status);
    }

    // virtual
    void db_loop::stop() noexcept
    {
        uv_stop(&_loop);
    }

    void db_loop::on_async() noexcept
    {
        while (!queue()->empty()) {
            auto task { queue()->dequeue() };
            handler()->handle_task(task);
        }
    }

    // static
    void db_loop::async_routine(uv_async_t *handle) noexcept
    {
        logassert(handle != nullptr, "Invalid handle.");
        logassert(handle->data != nullptr, "Invalid data.");
        static_cast<db_loop *>(handle->data)->on_async();
    }

}
