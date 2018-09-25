/**
 * @file message_request_task.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ROCKET_MESSAGE_REQUEST_TASK_H
#define ROCKET_MESSAGE_REQUEST_TASK_H

#include "task/basic_task.h"
#include "message/message.h"

namespace rocket {

    /**
     * Incoming message task.
     */
    class message_request_task final : public groot::crucial<basic_task, message_request_task> {
    public:
        GR_DECLARE_SMARTPOINTERS(message_request_task)
        GR_DELETE_ALL_DEFAULT(message_request_task)

        explicit message_request_task(message::opcode_type opcode, u8 *memory, size_t length) noexcept;
        virtual ~message_request_task();

    private:
        message::opcode_type    _opcode;
        u8 *                    _memory;
        size_t                  _length;

    };

}

#endif /* ROCKET_MESSAGE_REQUEST_TASK_H */
