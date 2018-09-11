//
// Created by Feo on 03/09/2018.
//

#include "db/connection/db_connection.h"

namespace rocket {

    db_connection::db_connection() :
            _connection { nullptr }
    {
    }

    db_connection::~db_connection()
    {
    }

    void db_connection::connect(const char *conninfo) noexcept
    {
        _connection = PQconnectStart(conninfo);
        if (_connection == nullptr) {
            logerror("Can't allocate memory for pq connection struct.");
            return;
        }

        if (PQstatus(_connection) == CONNECTION_BAD) {
            logerror("Failed to create pq connection struct.");
            _connection = nullptr;
            return;
        }
    }

    void db_connection::disconnect() noexcept
    {

    }

}
