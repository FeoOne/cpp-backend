/**
 * @file ws_response_task.h
 * @author Feo
 * @date 23/08/2018
 * @brief
 */

#ifndef ENGINE_WS_RESPONSE_TASK_H
#define ENGINE_WS_RESPONSE_TASK_H

#include <libsoup/soup.h>

#include "task/basic_task.h"

namespace engine {

    class ws_response_task : public stl::crucial<basic_task, ws_response_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(ws_response_task)
        STL_DELETE_ALL_DEFAULT(ws_response_task)

        explicit ws_response_task(SoupWebsocketConnection *connection, std::string&& data) noexcept :
                _connection { connection },
                _data { data }
        {}
        virtual ~ws_response_task() = default;

        SoupWebsocketConnection *connection() noexcept { return _connection; }
        const char *data() const noexcept { return _data.data(); }

    private:
        SoupWebsocketConnection *       _connection;
        std::string                     _data;

    };

}

#endif /* ENGINE_WS_RESPONSE_TASK_H */
