/**
 * @file outgoing_message_task.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ENGINE_OUTGOING_MESSAGE_TASK_H
#define ENGINE_OUTGOING_MESSAGE_TASK_H

#include "task/task.h"
#include "io/connection/connection.h"

namespace engine {

    class outgoing_message_task : public framework::crucial<task, outgoing_message_task> {
    public:
        FW_DECLARE_SMARTPOINTERS(outgoing_message_task)
        FW_DELETE_ALL_DEFAULT(outgoing_message_task)

        explicit outgoing_message_task(const connection::sptr& connection) noexcept : _connection { connection } {}
        virtual ~outgoing_message_task() = default;

        connection::sptr get_connection() const noexcept { return _connection; }

    private:
        connection::sptr        _connection;

    };

}

#endif /* ENGINE_OUTGOING_MESSAGE_TASK_H */
