/**
 * @file db_loop.cpp
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#include "db/db_loop.h"

namespace engine {

    db_loop::db_loop(const task_queue::sptr& queue, task_handler *handler) noexcept :
            work_loop(queue, handler)
    {
    }

    // virtual
    db_loop::~db_loop()
    {
    }

    // virtual
    void db_loop::start() noexcept
    {

    }

    // virtual
    void db_loop::stop() noexcept
    {

    }

}
