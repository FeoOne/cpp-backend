/**
 * @file close_connection_task.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ENGINE_CLOSE_CONNECTION_TASK_H
#define ENGINE_CLOSE_CONNECTION_TASK_H

#include "task/task.h"
#include "io/connection/connection.h"

namespace engine {

    class close_connection_task : public framework::crucial<task, close_connection_task> {
    public:
        FW_DECLARE_SMARTPOINTERS(close_connection_task)
        FW_DELETE_ALL_DEFAULT(close_connection_task)

        explicit close_connection_task(const connection::sptr& connection) noexcept : _connection { connection } {}
        virtual ~close_connection_task() = default;

        connection::sptr get_connection() const noexcept { return _connection; }

    private:
        connection::sptr        _connection;

    };

}

#endif /* ENGINE_CLOSE_CONNECTION_TASK_H */
