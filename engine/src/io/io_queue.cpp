/**
 * @file io_queue.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "io/io_queue.h"

namespace engine {

    io_queue::io_queue() :
            task_queue(engine_const::DOMAIN_TASK_QUEUE_SYSTEM)
    {
    }

    // virtual
    void io_queue::enqueue(const task::sptr& task) noexcept
    {

        push(task);
    }

    // virtual
    task::sptr io_queue::dequeue() noexcept
    {

        return pop();
    }

    // virtual
    bool io_queue::empty() const noexcept
    {

        return is_empty();
    }

}
