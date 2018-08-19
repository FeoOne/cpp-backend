/**
 * @file task_handler.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef ENGINE_TASK_HANDLER_H
#define ENGINE_TASK_HANDLER_H

#include "task/task.h"

namespace engine {

    class task_handler {
    public:
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(task_handler)

        virtual ~task_handler() = default;

        virtual void handle_task(const task::sptr& task) noexcept = 0;

    protected:
        task_handler() = default;

    };

}

#endif /* ENGINE_TASK_HANDLER_H */
