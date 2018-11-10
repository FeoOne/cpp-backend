//
// Created by Feo on 03/09/2018.
//

#ifndef ENGINE_DB_CONNECTION_H
#define ENGINE_DB_CONNECTION_H

#include <libpq-fe.h>

#include <stl.h>

#include "context/db/db_loop.h"
#include "context/io/net/network.h"

namespace engine {

    class db_request;

    class db_connection final {
    public:
        STL_DECLARE_SMARTPOINTERS(db_connection)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(db_connection)

        enum class connection_state {
            invalid,
            connecting,
            available,
        };

        db_connection();
        ~db_connection();

        bool start(db_loop *loop, const char *conninfo, void *data) noexcept;
        void finish() noexcept;

        bool start_polling(int events, uv_poll_cb fn) noexcept;
        void stop_polling() noexcept;

        PostgresPollingStatusType poll() noexcept;
        int consume_input() noexcept;
        PGnotify *notifies() noexcept;
        bool is_busy() noexcept;
        ConnStatusType status() const noexcept;
        PGresult *result() noexcept;
        const char *error_message() const noexcept;

        int send_request(db_request *request) noexcept;
        void flush() noexcept;

        connection_state state() const noexcept { return _state; }
        void set_state(connection_state state) noexcept { _state = state; }

        poll_handle *handle() noexcept { return &_handle; }

    private:
        poll_handle             _handle;
        PGconn *                _connection;
        connection_state        _state;

    };

}

#endif /* ENGINE_DB_CONNECTION_H */
