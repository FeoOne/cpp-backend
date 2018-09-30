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
    class io_response_task final : public groot::crucial<basic_task, io_response_task> {
    public:
        GR_DECLARE_SMARTPOINTERS(io_response_task)
        GR_DELETE_ALL_DEFAULT(io_response_task)

        explicit io_response_task(bool is_urgent) noexcept : _is_urgent { is_urgent } {}
        virtual ~io_response_task() = default;

        bool priority() const noexcept { return _is_urgent; }

    private:
        bool       _is_urgent;

    };

}

#endif /* ROCKET_MESSAGE_RESPONSE_TASK_H */
