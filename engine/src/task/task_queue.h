//
// Created by Feo on 16/08/2018.
//

#ifndef ENGINE_TASK_QUEUE_H
#define ENGINE_TASK_QUEUE_H

#include "task/task.h"
#include "task/task_queue_delegate.h"

namespace engine {

    class task_queue {
    public:
        FW_DECLARE_SMARTPOINTERS(task_queue)

        task_queue();

        void set_delegate(const task_queue_delegate::sptr& delegate) noexcept { _delegate = delegate; }

    private:
        task_queue_delegate::wptr       _delegate;

    };

}

#endif /* ENGINE_TASK_QUEUE_H */
