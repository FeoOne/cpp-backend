/**
 * @file connection_status_changed_task.h
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#ifndef ENGINE_CONNECTION_STATUS_CHANGED_TASK_H
#define ENGINE_CONNECTION_STATUS_CHANGED_TASK_H

#include "task/basic_task.h"
#include "context/io/connection/connection_link.h"

namespace engine {

    class connection_status_changed_task final : public stl::crucial<basic_task, connection_status_changed_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(connection_status_changed_task)
        STL_DELETE_ALL_DEFAULT(connection_status_changed_task)

        explicit connection_status_changed_task(const connection_link& link,
                                                connection_status status,
                                                connection_status previous_status) noexcept :
                _link { link },
                _status { status },
                _previous_status { previous_status }
        {}

        virtual ~connection_status_changed_task() = default;

        const connection_link& link() const noexcept { return _link; }
        connection_status status() const noexcept { return _status; }
        connection_status previous_status() const noexcept { return _previous_status; }

    private:
        connection_link         _link;
        connection_status       _status;
        connection_status       _previous_status;

    };

}

#endif /* ENGINE_CONNECTION_STATUS_CHANGED_TASK_H */
