/**
 * @file message_response_task.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ROCKET_MESSAGE_RESPONSE_TASK_H
#define ROCKET_MESSAGE_RESPONSE_TASK_H

#include "task/basic_task.h"

namespace rocket {

    /**
     * Outgoing message task.
     */
    class message_response_task final : public groot::crucial<basic_task, message_response_task> {
    public:
        GR_DECLARE_SMARTPOINTERS(message_response_task)
        GR_DELETE_ALL_DEFAULT(message_response_task)

        enum class priority {
            urgent,
            delayed
        };

        explicit message_response_task(priority pri) noexcept : _priority { pri } {}
        virtual ~message_response_task() = default;



    private:
        priority        _priority;

    };

}

#endif /* ROCKET_MESSAGE_RESPONSE_TASK_H */
