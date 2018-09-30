/**
 * @file ws_outgoing_message_task.h
 * @author Feo
 * @date 23/08/2018
 * @brief
 */

#ifndef ENGINE_WS_OUTGOING_MESSAGE_TASK_H
#define ENGINE_WS_OUTGOING_MESSAGE_TASK_H

#include <libsoup/soup.h>

#include "task/basic_task.h"

namespace engine {

    class ws_outgoing_message_task : public stl::crucial<basic_task, ws_outgoing_message_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(ws_outgoing_message_task)
        STL_DELETE_ALL_DEFAULT(ws_outgoing_message_task)

        explicit ws_outgoing_message_task(SoupWebsocketConnection *connection, GBytes *data, size_t size) noexcept :
                _connection { connection }
//                _data { data },
//                _size { size }
        {}
        virtual ~ws_outgoing_message_task() = default;

        SoupWebsocketConnection *get_connection() noexcept { return _connection; }

    private:
        SoupWebsocketConnection *       _connection;
//        GBytes *                        _data;
//        size_t                          _size;

    };

}

#endif /* ENGINE_WS_OUTGOING_MESSAGE_TASK_H */
