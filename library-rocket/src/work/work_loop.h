/**
 * @file execution_loop.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ROCKET_EXECUTION_LOOP_H
#define ROCKET_EXECUTION_LOOP_H

#include "task/task_queue.h"
#include "task/task_handler.h"

namespace rocket {

    class work_loop {
    public:
        GR_DECLARE_SMARTPOINTERS(work_loop)
        GR_DELETE_ALL_DEFAULT(work_loop)

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

#endif /* ROCKET_EXECUTION_LOOP_H */
