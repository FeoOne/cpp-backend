/**
 * @file db_queue.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "db/db_queue.h"

namespace rocket {

    // todo: not implemeted

    db_queue::db_queue() :
            task_queue(consts::DOMAIN_TASK_QUEUE_SYSTEM)
    {
    }

    // virtual
    void db_queue::enqueue(basic_task *task) noexcept
    {

        push(task);
    }

    // virtual
    basic_task *db_queue::dequeue() noexcept
    {

        return pop();
    }

    // virtual
    bool db_queue::empty() const noexcept
    {

        return is_empty();
    }

}
