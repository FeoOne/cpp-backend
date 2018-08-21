/**
 * @file new_connection_task.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ENGINE_NEW_CONNECTION_TASK_H
#define ENGINE_NEW_CONNECTION_TASK_H

#include "task/task.h"
#include "io/connection/connection.h"

namespace engine {

    class new_connection_task : public framework::crucial<task, new_connection_task> {
    public:
        FW_DECLARE_SMARTPOINTERS(new_connection_task)
        FW_DELETE_ALL_DEFAULT(new_connection_task)

        explicit new_connection_task(const connection::sptr& connection) noexcept : _connection { connection } {}
        virtual ~new_connection_task() = default;

        connection::sptr get_connection() const noexcept { return _connection; }

    private:
        connection::sptr        _connection;

    };

}

#endif /* ENGINE_NEW_CONNECTION_TASK_H */
