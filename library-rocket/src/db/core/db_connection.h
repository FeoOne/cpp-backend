//
// Created by Feo on 03/09/2018.
//

#ifndef ROCKET_DB_CONNECTION_H
#define ROCKET_DB_CONNECTION_H

#include <libpq-fe.h>

#include <groot.h>

#include "db/db_loop.h"

namespace rocket {

    class db_connection final {
    public:
        GR_DECLARE_SMARTPOINTERS(db_connection)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(db_connection)

        enum class status {
            invalid,
            disconnecting,
            validating,
            connecting,
            available,
            busy,
        };

        db_connection();
        ~db_connection();

        bool start(db_loop *loop, const char *conninfo) noexcept;
        void finish() noexcept;

        status get_status() const noexcept { return _status; }

    private:
        status                  _status;
        groot::network_handle   _handle;
        PGconn *                _connection;

    };

}

#endif /* ROCKET_DB_CONNECTION_H */
