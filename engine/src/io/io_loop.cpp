/**
 * @file io_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "events/events.h"

#include "io/io_loop.h"

namespace engine {

    io_loop::io_loop(const event_queue::sptr& queue) noexcept :
            work_loop(queue),
            _loop { std::make_unique<uv_loop_t>() },
            _async_handler { std::make_unique<uv_async_t>() }
    {
        uv_loop_init(_loop.get());
    }

    // virtual
    io_loop::~io_loop()
    {
        uv_loop_close(_loop.get());
    }

    // virtual
    void io_loop::run() noexcept
    {
        int status = uv_async_init(_loop.get(), _async_handler.get(), &io_loop::notify_callback);
        if (status == 0) {
            _async_handler->data = this;
        } else {
            // @todo Check status.
        }

        status = uv_run(_loop.get(), UV_RUN_DEFAULT);

        loginfo("UV loop terminated with %d active handles or requests.", status);
    }

    // virtual
    void io_loop::stop() noexcept
    {
        loginfo("Performing stop for loop.");

        uv_stop(_loop.get());
    }

    // virtual
    bool io_loop::stopped() const noexcept
    {
        return (uv_loop_alive(_loop.get()) == 0);
    }

    // virtual
    void io_loop::wakeup() noexcept
    {
        /*int status =*/ uv_async_send(_async_handler.get());
        // @todo Check status for error.
    }

    void io_loop::notify_callback() noexcept
    {
        event::sptr eve { nullptr };
        do {
            eve = get_queue()->dequeue();
            if (eve != nullptr) {
                logdebug("Dequeued event with key: %lu, name: '%s'.",
                         eve->get_key(),
                         event_name_from_key(eve->get_key()).data());
                handle_event(eve);
            }
        } while (eve);
    }

    // static
    void io_loop::notify_callback(uv_async_t *handle) noexcept
    {
        // @todo Handle error.
        reinterpret_cast<io_loop *>(handle->data)->notify_callback();
    }

}
