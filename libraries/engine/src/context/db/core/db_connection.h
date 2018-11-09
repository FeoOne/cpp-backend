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

        enum class state {
            invalid,
            connecting,
            resetting,
            bad_connect,
            bad_reset,
            available,
        };

        db_connection();
        ~db_connection();

        bool start(db_loop *loop, const char *conninfo) noexcept;
        void finish() noexcept;

        PostgresPollingStatusType poll() noexcept;
        int consume_input() noexcept;
        PGnotify *notifies() noexcept;
        bool is_busy() noexcept;

        state status() const noexcept { return _state; }
        void status(state new_state) noexcept { _state = new_state; }
        poll_handle *handle() noexcept { return &_handle; }

        const char *error_message() const noexcept { return PQerrorMessage(_connection); }

        int send_query(db_request *request) noexcept;
        void flush() noexcept;

    private:
        state                   _state;
        poll_handle             _handle;
        PGconn *                _connection;
        bool                    _is_new;

    };

}

#endif /* ENGINE_DB_CONNECTION_H */
