/**
 * @file incoming_message_task.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ROCKET_INCOMING_MESSAGE_TASK_H
#define ROCKET_INCOMING_MESSAGE_TASK_H

#include "task/task.h"

namespace rocket {

    class incoming_message_task : public groot::crucial<task, incoming_message_task> {
    public:
        GR_DECLARE_SMARTPOINTERS(incoming_message_task)
        GR_DELETE_ALL_DEFAULT(incoming_message_task)

        explicit incoming_message_task(nullptr_t) noexcept {}
        virtual ~incoming_message_task() = default;



    private:


    };

}

#endif /* ROCKET_INCOMING_MESSAGE_TASK_H */
