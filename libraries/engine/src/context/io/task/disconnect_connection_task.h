/**
 * @file disconnect_connection_task.h
 * @author Feo
 * @date 19/10/2018
 * @brief
 */

#ifndef ENGINE_DISCONNECT_CONNECTION_TASK_H
#define ENGINE_DISCONNECT_CONNECTION_TASK_H

#include "task/basic_task.h"
#include "context/io/connection/connection_link.h"

namespace engine {

    class disconnect_connection_task : public stl::crucial<basic_task, disconnect_connection_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(disconnect_connection_task)
        STL_DELETE_ALL_DEFAULT(disconnect_connection_task)

        explicit disconnect_connection_task(const connection_link& link) noexcept :
                _link { link }
        {}

        virtual ~disconnect_connection_task() = default;

        const connection_link& link() const noexcept { return _link; }

    private:
        connection_link         _link;

    };

}

#endif /* ENGINE_DISCONNECT_CONNECTION_TASK_H */
