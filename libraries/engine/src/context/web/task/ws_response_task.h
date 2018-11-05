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

        explicit ws_response_task(SoupWebsocketConnection *connection, GBytes *data, size_t size) noexcept :
                _connection { connection }
//                _data { data },
//                _size { size }
        {}
        virtual ~ws_response_task() = default;

        SoupWebsocketConnection *connection() noexcept { return _connection; }

    private:
        SoupWebsocketConnection *       _connection;
//        GBytes *                        _data;
//        size_t                          _size;

    };

}

#endif /* ENGINE_WS_RESPONSE_TASK_H */
