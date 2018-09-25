/**
 * @file db_queue.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ROCKET_DB_QUEUE_H
#define ROCKET_DB_QUEUE_H

#include "task/task_queue.h"

namespace rocket {

    class db_queue final : public task_queue {
    public:
        GR_DECLARE_SMARTPOINTERS(db_queue)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(db_queue)

        db_queue();
        virtual ~db_queue() = default;

        void enqueue(basic_task *task) noexcept final;
        basic_task *dequeue() noexcept final;

        bool empty() const noexcept final;

    private:

    };

}

#endif /* ROCKET_DB_QUEUE_H */
