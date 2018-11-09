//
// Created by Feo on 03/09/2018.
//

#include "context/db/core/db_types.h"
#include "context/db/core/db_request.h"

#include "context/db/core/db_connection.h"

namespace engine {

    db_connection::db_connection() :
            _state { state::invalid },
            _handle {},
            _connection { nullptr },
            _is_new { true }
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

            int fd = PQsocket(_connection);
            fd = fcntl(fd, F_DUPFD_CLOEXEC, 0);
            if (fd < 0) {
                logerror("Failed to dup fd (%s).", strerror(errno));
                break;
            }

            int status = uv_poll_init_socket(loop->get_loop(), &_handle.poll, fd);
            if (status != 0) {
                logerror("Failed to poll fd (%s).", uv_err_name(status));
                break;
            }

            _state = state::connecting;

            poll();

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

    PostgresPollingStatusType db_connection::poll() noexcept
    {
        if (_state == state::resetting) {
            return PQresetPoll(_connection);
        }

        return PQconnectPoll(_connection);
    }

    int db_connection::consume_input() noexcept
    {
        return PQconsumeInput(_connection);
    }

    PGnotify *db_connection::notifies() noexcept
    {
        return PQnotifies(_connection);
    }

    bool db_connection::is_busy() noexcept
    {
        return PQisBusy(_connection) == 1;
    }

    int db_connection::send_query(db_request *request) noexcept
    {
        request->assign_connection(this);

        return PQsendQueryParams(_connection,
                request->query().data(),
                static_cast<int>(request->params().count()),
                request->params().oids(),
                request->params().values(),
                request->params().lengths(),
                request->params().formats(),
                FORMAT_BINARY);
    }

    void db_connection::flush() noexcept
    {
        PQflush(_connection);
    }

}
