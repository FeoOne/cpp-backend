//
// Created by Feo on 16/11/2018.
//

#ifndef ENGINE_WS_CONNECTION_STATUS_TASK_H
#define ENGINE_WS_CONNECTION_STATUS_TASK_H

#include <libsoup/soup.h>

#include "task/basic_task.h"
#include "context/io/net/network.h"

namespace engine {

    class ws_connection_status_task final : public stl::crucial<basic_task, ws_connection_status_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(ws_connection_status_task)
        STL_DELETE_ALL_DEFAULT(ws_connection_status_task)

        explicit ws_connection_status_task(SoupWebsocketConnection *connection, connection_status status) noexcept :
                _connection { connection },
                _status { status }
        {}

        virtual ~ws_connection_status_task() = default;

        SoupWebsocketConnection *connection() const noexcept { return _connection; }
        connection_status status() const noexcept { return _status; }

    private:
        SoupWebsocketConnection *       _connection;
        connection_status               _status;

    };

}

#endif /* ENGINE_WS_CONNECTION_STATUS_TASK_H */
