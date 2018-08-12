/**
 * @file io_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "io/io_loop.h"

namespace engine {

    io_loop::io_loop(const event_queue::sptr& queue) noexcept :
            execution_loop(queue),
            _loop {}
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
        int result = uv_run(_loop.get(), UV_RUN_DEFAULT);

        loginfo("UV loop terminated with %d active handles or requests.", result);
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

}
