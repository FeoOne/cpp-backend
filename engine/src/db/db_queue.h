/**
 * @file db_queue.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ENGINE_DB_QUEUE_H
#define ENGINE_DB_QUEUE_H

#include "task/task_queue.h"

namespace engine {

    class db_queue final : public task_queue {
    public:
        FW_DECLARE_SMARTPOINTERS(db_queue)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(db_queue)

        db_queue();
        virtual ~db_queue() = default;

        void enqueue(const task::sptr& task) noexcept final;
        task::sptr dequeue() noexcept final;

        bool empty() const noexcept final;

    private:

    };

}

#endif /* ENGINE_DB_QUEUE_H */
