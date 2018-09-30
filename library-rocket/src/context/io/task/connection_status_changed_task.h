/**
 * @file connection_status_changed_task.h
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#ifndef ROCKET_CONNECTION_STATUS_CHANGED_TASK_H
#define ROCKET_CONNECTION_STATUS_CHANGED_TASK_H

#include "task/basic_task.h"
#include "context/io/connection/connection_link.h"

namespace rocket {

    class connection_status_changed_task : public groot::crucial<basic_task, connection_status_changed_task> {
    public:
        GR_DECLARE_SMARTPOINTERS(connection_status_changed_task)
        GR_DELETE_ALL_DEFAULT(connection_status_changed_task)

        explicit connection_status_changed_task(const connection_link& link, connection_status status) noexcept :
                _link { link },
                _status { status }
        {}

        virtual ~connection_status_changed_task() = default;

        const connection_link& link() const noexcept { return _link; }
        connection_status status() const noexcept { return _status; }

    private:
        connection_link         _link;
        connection_status       _status;

    };

}

#endif /* ROCKET_CONNECTION_STATUS_CHANGED_TASK_H */
