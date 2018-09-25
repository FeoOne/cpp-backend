/**
 * @file io_queue.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "io/io_queue.h"

namespace rocket {

    io_queue::io_queue() :
            task_queue(consts::DOMAIN_TASK_QUEUE_SYSTEM)
    {
    }

    // virtual
    void io_queue::enqueue(basic_task *task) noexcept
    {

        push(task);
    }

    // virtual
    basic_task *io_queue::dequeue() noexcept
    {

        return pop();
    }

    // virtual
    bool io_queue::empty() const noexcept
    {

        return is_empty();
    }

}
