/**
 * @file quiet_task_queue.h
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#ifndef ENGINE_QUIET_TASK_QUEUE_H
#define ENGINE_QUIET_TASK_QUEUE_H

#include "task/queue/task_queue.h"

namespace engine {

    class quiet_task_queue final : public task_queue {
    public:
        STL_DECLARE_SMARTPOINTERS(quiet_task_queue)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(quiet_task_queue)

        quiet_task_queue();
        virtual ~quiet_task_queue() = default;

        void enqueue(basic_task *task) noexcept final;
        basic_task *dequeue() noexcept final;

        bool empty() const noexcept final;

        inline void set_notify_fn(std::function<void()>&& fn) noexcept { _notify_fn = std::move(fn); }

    private:
        mutable std::timed_mutex        _mutex;
        std::function<void()>           _notify_fn;

    };

}

#endif /* ENGINE_QUIET_TASK_QUEUE_H */
