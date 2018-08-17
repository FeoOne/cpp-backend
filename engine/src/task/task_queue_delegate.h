//
// Created by Feo on 16/08/2018.
//

#ifndef ENGINE_TASK_QUEUE_DELEGATE_H
#define ENGINE_TASK_QUEUE_DELEGATE_H

#include <framework.h>

namespace engine {

    class task_queue_delegate {
    public:
        FW_DECLARE_SMARTPOINTERS(task_queue_delegate)

        virtual ~task_queue_delegate() = default;

        virtual void on_new_task() noexcept = 0;

    protected:
        task_queue_delegate() = default;

    };

}

#endif /* ENGINE_TASK_QUEUE_DELEGATE_H */
