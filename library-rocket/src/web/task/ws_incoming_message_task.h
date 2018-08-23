/**
 * @file ws_incoming_message_task.h
 * @author Feo
 * @date 23/08/2018
 * @brief
 */

#ifndef ROCKET_WS_INCOMING_MESSAGE_TASK_H
#define ROCKET_WS_INCOMING_MESSAGE_TASK_H

#include <libsoup/soup.h>

#include <groot.h>

#include "task/task.h"

namespace rocket {

    class ws_incoming_message_task : public groot::crucial<task, ws_incoming_message_task> {
    public:
        GR_DECLARE_SMARTPOINTERS(ws_incoming_message_task)
        GR_DELETE_ALL_DEFAULT(ws_incoming_message_task)

        explicit ws_incoming_message_task(SoupWebsocketConnection *connection,
                                          SoupWebsocketDataType data_type,
                                          GBytes *data) noexcept :
                _connection { connection },
                _data_type { data_type },
                _data { data }
        {
            _data = GR_GOBJECT_REF(_data);
        }

        virtual ~ws_incoming_message_task()
        {
            GR_GOBJECT_UNREF(_data)
        }

        SoupWebsocketConnection *get_connection() noexcept { return _connection; }

    private:
        SoupWebsocketConnection *       _connection;
        SoupWebsocketDataType           _data_type;
        GBytes *                        _data;

    };

}

#endif /* ROCKET_WS_INCOMING_MESSAGE_TASK_H */
