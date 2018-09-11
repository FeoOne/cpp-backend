//
// Created by Feo on 03/09/2018.
//

#ifndef ROCKET_DB_CONNECTION_H
#define ROCKET_DB_CONNECTION_H

#include <libpq-fe.h>

#include <groot.h>

namespace rocket {

    class db_connection final {
    public:
        GR_DECLARE_SMARTPOINTERS(db_connection)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(db_connection)

        db_connection();
        ~db_connection();

        void connect(const char *conninfo) noexcept;
        void disconnect() noexcept;
        

    private:
        PGconn *            _connection;

    };

}

#endif /* ROCKET_DB_CONNECTION_H */
