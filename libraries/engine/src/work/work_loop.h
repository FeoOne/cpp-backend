/**
 * @file execution_loop.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTION_LOOP_H
#define ENGINE_EXECUTION_LOOP_H

#include "task/task_handler.h"
#include "task/queue/task_queue.h"

namespace engine {

    class work_loop {
    public:
        STL_DECLARE_SMARTPOINTERS(work_loop)
        STL_DELETE_ALL_DEFAULT(work_loop)

        virtual ~work_loop() = default;

        virtual void start() noexcept = 0;
        virtual void stop() noexcept = 0;

    protected:
        explicit work_loop(task_queue *queue, const task_handler *handler) noexcept :
                _queue { queue },
                _handler { handler }
        {}

        task_queue *queue() const noexcept { return _queue; }
        const task_handler *handler() noexcept { return _handler; }

    private:
        task_queue *                _queue;
        const task_handler *        _handler;

    };

}

#endif /* ENGINE_EXECUTION_LOOP_H */
