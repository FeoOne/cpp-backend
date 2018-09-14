//
// Created by Feo on 03/09/2018.
//

#include "db/core/db_connection.h"

namespace rocket {

    db_connection::db_connection() :
            _status { status::invalid },
            _handle {},
            _connection { nullptr }
    {
    }

    db_connection::~db_connection()
    {
    }

    bool db_connection::start(db_loop *loop, const char *conninfo) noexcept
    {
        while (true) {
            _connection = PQconnectStart(conninfo);
            if (_connection == nullptr) {
                logerror("Can't allocate memory for pq connection struct.");
                break;
            }

            if (PQstatus(_connection) == CONNECTION_BAD) {
                logerror("Failed to create pq connection struct (%s).", PQerrorMessage(_connection));
                break;
            }

            int status = uv_tcp_init(loop->get_loop(), &_handle.tcp);
            if (status != 0) {
                logerror("Failed to create network handle (%s).", uv_err_name(status));
                break;
            }

            status = uv_tcp_open(&_handle.tcp, PQsocket(_connection));
            if (status != 0) {
                logerror("Failed to setup tcp socket (%s).", uv_err_name(status));
                break;
            }

            _handle.handle.data = this;

            _status = status::connecting;

            return true;
        }

        finish();

        return false;
    }

    void db_connection::finish() noexcept
    {
        if (_connection != nullptr) {
            PQfinish(_connection);
            _connection = nullptr;
        }
    }

}
