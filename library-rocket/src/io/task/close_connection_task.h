/**
 * @file close_connection_task.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ROCKET_CLOSE_CONNECTION_TASK_H
#define ROCKET_CLOSE_CONNECTION_TASK_H

#include "task/task.h"
#include "io/connection/connection.h"

namespace rocket {

    class close_connection_task : public groot::crucial<task, close_connection_task> {
    public:
        GR_DECLARE_SMARTPOINTERS(close_connection_task)
        GR_DELETE_ALL_DEFAULT(close_connection_task)

        explicit close_connection_task(const connection::sptr& connection) noexcept : _connection { connection } {}
        virtual ~close_connection_task() = default;

        connection::sptr get_connection() const noexcept { return _connection; }

    private:
        connection::sptr        _connection;

    };

}

#endif /* ROCKET_CLOSE_CONNECTION_TASK_H */
