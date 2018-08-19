/**
 * @file io_queue.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ENGINE_IO_QUEUE_H
#define ENGINE_IO_QUEUE_H

#include "task/task_queue.h"

namespace engine {

    class io_queue final : public task_queue {
    public:
        FW_DECLARE_SMARTPOINTERS(io_queue)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(io_queue)

        io_queue();
        virtual ~io_queue() = default;

        void enqueue(const task::sptr& task) noexcept final;
        task::sptr dequeue() noexcept final;

        bool empty() const noexcept final;

    private:

    };

}

#endif /* ENGINE_IO_QUEUE_H */
