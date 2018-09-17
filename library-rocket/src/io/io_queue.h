/**
 * @file io_queue.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ROCKET_IO_QUEUE_H
#define ROCKET_IO_QUEUE_H

#include "task/task_queue.h"

namespace rocket {

    class io_queue final : public task_queue {
    public:
        GR_DECLARE_SMARTPOINTERS(io_queue)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(io_queue)

        io_queue();
        virtual ~io_queue() = default;

        void enqueue(const task::sptr& task) noexcept final;
        task::sptr dequeue() noexcept final;

        bool empty() const noexcept final;

    private:

    };

}

#endif /* ROCKET_IO_QUEUE_H */
