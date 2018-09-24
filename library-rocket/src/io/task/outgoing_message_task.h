/**
 * @file outgoing_message_task.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ROCKET_OUTGOING_MESSAGE_TASK_H
#define ROCKET_OUTGOING_MESSAGE_TASK_H

#include "task/task.h"

namespace rocket {

    class outgoing_message_task final : public groot::crucial<task, outgoing_message_task> {
    public:
        GR_DECLARE_SMARTPOINTERS(outgoing_message_task)
        GR_DELETE_ALL_DEFAULT(outgoing_message_task)

        enum class priority {
            urgent,
            delayed
        };

        explicit outgoing_message_task(priority pri) noexcept : _priority { pri } {}
        virtual ~outgoing_message_task() = default;



    private:
        priority        _priority;

    };

}

#endif /* ROCKET_OUTGOING_MESSAGE_TASK_H */
