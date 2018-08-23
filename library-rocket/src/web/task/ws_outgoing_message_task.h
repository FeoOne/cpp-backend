/**
 * @file ws_outgoing_message_task.h
 * @author Feo
 * @date 23/08/2018
 * @brief
 */

#ifndef ROCKET_WS_OUTGOING_MESSAGE_TASK_H
#define ROCKET_WS_OUTGOING_MESSAGE_TASK_H

#include <libsoup/soup.h>

#include "task/task.h"

namespace rocket {

    class ws_outgoing_message_task : public groot::crucial<task, ws_outgoing_message_task> {
    public:
        GR_DECLARE_SMARTPOINTERS(ws_outgoing_message_task)
        GR_DELETE_ALL_DEFAULT(ws_outgoing_message_task)

        explicit ws_outgoing_message_task(SoupWebsocketConnection *connection) noexcept : _connection { connection } {}
        virtual ~ws_outgoing_message_task() = default;

        SoupWebsocketConnection *get_connection() noexcept { return _connection; }

    private:
        SoupWebsocketConnection *       _connection;

    };

}

#endif /* ROCKET_WS_OUTGOING_MESSAGE_TASK_H */
