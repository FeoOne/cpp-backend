/**
 * @file ws_disconnect_task.h
 * @author Feo
 * @date 05/11/2018
 * @brief
 */

#ifndef ENGINE_WS_DISCONNECT_TASK_H
#define ENGINE_WS_DISCONNECT_TASK_H

#include <libsoup/soup.h>

#include "task/basic_task.h"

namespace engine {

    class ws_disconnect_task : public stl::crucial<basic_task, ws_disconnect_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(ws_disconnect_task)
        STL_DELETE_ALL_DEFAULT(ws_disconnect_task)

        explicit ws_disconnect_task(SoupWebsocketConnection *connection) noexcept :
                _code { SoupWebsocketCloseCode::SOUP_WEBSOCKET_CLOSE_NORMAL },
                _connection { connection }
        {}

        explicit ws_disconnect_task(SoupWebsocketConnection *connection, SoupWebsocketCloseCode code) noexcept :
                _code { code },
                _connection { connection }
        {}

        virtual ~ws_disconnect_task() = default;

        SoupWebsocketConnection *connection() noexcept { return _connection; }
        SoupWebsocketCloseCode code() const noexcept { return _code; }

    private:
        SoupWebsocketCloseCode          _code;
        SoupWebsocketConnection *       _connection;
    };

}

#endif /* ENGINE_WS_DISCONNECT_TASK_H */
