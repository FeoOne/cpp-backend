/**
 * @file outgoing_message_task.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ROCKET_OUTGOING_MESSAGE_TASK_H
#define ROCKET_OUTGOING_MESSAGE_TASK_H

#include "task/task.h"
#include "io/connection/connection.h"

namespace rocket {

    class outgoing_message_task : public groot::crucial<task, outgoing_message_task> {
    public:
        GR_DECLARE_SMARTPOINTERS(outgoing_message_task)
        GR_DELETE_ALL_DEFAULT(outgoing_message_task)

        explicit outgoing_message_task(const connection::sptr& connection) noexcept : _connection { connection } {}
        virtual ~outgoing_message_task() = default;

        connection::sptr get_connection() const noexcept { return _connection; }

    private:
        connection::sptr        _connection;

    };

}

#endif /* ROCKET_OUTGOING_MESSAGE_TASK_H */
