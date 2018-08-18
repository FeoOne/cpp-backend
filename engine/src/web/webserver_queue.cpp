/**
 * @file webserver_queue.cpp
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#include "web/webserver_queue.h"

namespace engine {

    webserver_queue::webserver_queue() :
            task_queue(engine_const::DOMAIN_TASK_QUEUE_WEBSERVER),
            _mutex {}
    {
    }

    // virtual
    void webserver_queue::enqueue(const task::sptr& task) noexcept
    {
        std::unique_lock<std::timed_mutex> lock { _mutex };
        push(task);
    }

    // virtual
    task::sptr webserver_queue::dequeue() noexcept
    {
        std::unique_lock<std::timed_mutex> lock { _mutex };
        return pop();
    }

    // virtual
    bool webserver_queue::empty() const noexcept
    {
        std::unique_lock<std::timed_mutex> lock { _mutex };
        return is_empty();
    }

}
