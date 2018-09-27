//
// Created by Feo on 03/09/2018.
//

#ifndef ROCKET_DB_CONNECTION_H
#define ROCKET_DB_CONNECTION_H

#include <libpq-fe.h>

#include <groot.h>

#include "context/db/db_loop.h"

namespace rocket {

    class db_connection final {
    public:
        GR_DECLARE_SMARTPOINTERS(db_connection)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(db_connection)

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

        void poll() noexcept;

        state get_state() const noexcept { return _state; }

    private:
        state                   _state;
        uv_poll_t               _handle;
        PGconn *                _connection;

    };

}

#endif /* ROCKET_DB_CONNECTION_H */
