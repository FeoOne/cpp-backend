/**
 * @file io_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "io/io_loop.h"

namespace engine {

    io_loop::io_loop(const task_queue::sptr& queue, task_handler *handler) noexcept :
            work_loop(queue, handler)
    {
    }

    // virtual
    io_loop::~io_loop()
    {
    }

    // virtual
    void io_loop::start() noexcept
    {

    }

    // virtual
    void io_loop::stop() noexcept
    {

    }

}
