/**
 * @file incoming_message_task.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ROCKET_INCOMING_MESSAGE_TASK_H
#define ROCKET_INCOMING_MESSAGE_TASK_H

#include "task/task.h"
#include "io/connection/connection.h"

namespace rocket {

    class incoming_message_task : public groot::crucial<task, incoming_message_task> {
    public:
        FW_DECLARE_SMARTPOINTERS(incoming_message_task)
        FW_DELETE_ALL_DEFAULT(incoming_message_task)

        explicit incoming_message_task(const connection::sptr& connection) noexcept : _connection { connection } {}
        virtual ~incoming_message_task() = default;

        connection::sptr get_connection() const noexcept { return _connection; }

    private:
        connection::sptr        _connection;

    };

}

#endif /* ROCKET_INCOMING_MESSAGE_TASK_H */
