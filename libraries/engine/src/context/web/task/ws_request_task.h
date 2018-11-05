/**
 * @file ws_request_task.h
 * @author Feo
 * @date 23/08/2018
 * @brief
 */

#ifndef ENGINE_WS_REQUEST_TASK_H
#define ENGINE_WS_REQUEST_TASK_H

#include <libsoup/soup.h>

#include <stl.h>

#include "task/basic_task.h"

namespace engine {

    class ws_request_task : public stl::crucial<basic_task, ws_request_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(ws_request_task)
        STL_DELETE_ALL_DEFAULT(ws_request_task)

        explicit ws_request_task(SoupWebsocketConnection *connection,
                                          SoupWebsocketDataType data_type,
                                          GBytes *data) noexcept :
                _connection { connection },
                _data_type { data_type },
                _data { data }
        {
            _data = g_bytes_ref(_data);
        }

        virtual ~ws_request_task()
        {
            g_bytes_unref(_data);
        }

        SoupWebsocketConnection *connection() noexcept { return _connection; }
        SoupWebsocketDataType data_type() const noexcept { return _data_type; }

        const char *text(gsize *size) const noexcept {
            return reinterpret_cast<const char *>(g_bytes_get_data(_data, size));
        }

//        const packet_header *get_header() const noexcept {
//            //logassert(_data_type == SOUP_WEBSOCKET_DATA_BINARY);
//            gsize sz;
//            auto data = reinterpret_cast<const packet_header *>(g_bytes_get_data(_data, &sz));
//            return data;
//        }
//
//        const u8 *get_binary() const noexcept {
//            //logassert(_data_type == SOUP_WEBSOCKET_DATA_BINARY);
//            gsize sz;
//            auto data = &(reinterpret_cast<const u8 *>(g_bytes_get_data(_data, &sz))[sizeof(packet_header)]);
//            return data;
//        }

        GBytes *bytes() noexcept { return _data; }

    private:
        SoupWebsocketConnection *       _connection;
        SoupWebsocketDataType           _data_type;
        GBytes *                        _data;

    };

}

#endif /* ENGINE_WS_REQUEST_TASK_H */
