/**
 * @file db_queue.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "db/db_queue.h"

namespace engine {

    db_queue::db_queue() :
            task_queue(engine_const::DOMAIN_TASK_QUEUE_SYSTEM)
    {
    }

    // virtual
    void db_queue::enqueue(const task::sptr& task) noexcept
    {

        push(task);
    }

    // virtual
    task::sptr db_queue::dequeue() noexcept
    {

        return pop();
    }

    // virtual
    bool db_queue::empty() const noexcept
    {

        return is_empty();
    }

}
