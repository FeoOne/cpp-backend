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
#include "protocol/protocol_machine.h"

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
            _data = g_bytes_ref(_data);
        }

        virtual ~ws_incoming_message_task()
        {
            g_bytes_unref(_data);
        }

        SoupWebsocketConnection *get_connection() noexcept { return _connection; }
        SoupWebsocketDataType get_data_type() const noexcept { return _data_type; }
        const protocol_header *get_header() const noexcept {
            return (_data_type == SOUP_WEBSOCKET_DATA_BINARY) ?
                   reinterpret_cast<protocol_header *>(_data) :
                   nullptr;
        }
        const char *get_data() const noexcept {
            return (_data_type == SOUP_WEBSOCKET_DATA_BINARY) ?
                   &(reinterpret_cast<char *>(_data)[sizeof(protocol_header)]) :
                   reinterpret_cast<char *>(_data);
        }

        GBytes *get_bytes() noexcept { return _data; }

    private:
        SoupWebsocketConnection *       _connection;
        SoupWebsocketDataType           _data_type;
        GBytes *                        _data;

    };

}

#endif /* ROCKET_WS_INCOMING_MESSAGE_TASK_H */
