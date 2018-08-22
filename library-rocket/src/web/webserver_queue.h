//
// Created by Feo on 17/08/2018.
//

#ifndef ROCKET_WEBSERVER_QUEUE_H
#define ROCKET_WEBSERVER_QUEUE_H

#include "task/task_queue.h"

namespace rocket {

    class webserver_queue final : public task_queue {
    public:
        GR_DECLARE_SMARTPOINTERS(webserver_queue)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(webserver_queue)

        webserver_queue();
        virtual ~webserver_queue() = default;

        void enqueue(const task::sptr& task) noexcept final;
        task::sptr dequeue() noexcept final;

        bool empty() const noexcept final;

    public:
        mutable std::timed_mutex        _mutex;

    };

}

#endif /* ROCKET_WEBSERVER_QUEUE_H */
