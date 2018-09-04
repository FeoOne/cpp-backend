//
// Created by Feo on 03/09/2018.
//

#ifndef ROCKET_DB_CONNECTION_H
#define ROCKET_DB_CONNECTION_H

#include <libpq-fe.h>

#include <groot.h>

namespace rocket {

    class db_connection {
    public:
        GR_DECLARE_SMARTPOINTERS(db_connection)
        GR_DELETE_ALL_DEFAULT(db_connection)

        explicit db_connection(nullptr_t) noexcept;
        ~db_connection() = default;

    private:
        PGconn *        _connection;

    };

}

#endif /* ROCKET_DB_CONNECTION_H */
