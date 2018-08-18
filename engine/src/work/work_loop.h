/**
 * @file execution_loop.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTION_LOOP_H
#define ENGINE_EXECUTION_LOOP_H

#include <framework.h>

#include "task/task_queue.h"

namespace engine {

    class work_loop {
    public:
        FW_DECLARE_SMARTPOINTERS(work_loop)
        FW_DELETE_ALL_DEFAULT(work_loop)

        explicit work_loop(const task_queue::sptr& queue) noexcept;
        virtual ~work_loop() = default;

        virtual void start() noexcept = 0;
        virtual void stop() noexcept = 0;

    protected:
        task_queue::sptr get_queue() const noexcept { return _queue; }

    private:
        task_queue::sptr        _queue;

    };

}

#endif /* ENGINE_EXECUTION_LOOP_H */
