/**
 * @file system_queue.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_SYSTEM_QUEUE_H
#define ENGINE_SYSTEM_QUEUE_H

#include "task/task_queue.h"

namespace engine {

    class system_queue final : public task_queue {
    public:
        FW_DECLARE_SMARTPOINTERS(system_queue)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(system_queue)

        system_queue();
        virtual ~system_queue() = default;

        void enqueue(const task::sptr& task) noexcept final;
        task::sptr dequeue() noexcept final;

        bool empty() const noexcept final;

    private:
        std::condition_variable     _cv;
        mutable std::mutex          _mutex;

    };

}

#endif /* ENGINE_SYSTEM_QUEUE_H */
