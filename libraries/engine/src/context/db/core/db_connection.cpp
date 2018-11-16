//
// Created by Feo on 03/09/2018.
//

#include "context/db/core/db_types.h"
#include "context/db/core/db_request.h"

#include "context/db/core/db_connection.h"

namespace engine {

    db_connection::db_connection() :
            _handle {},
            _connection { nullptr },
            _state { connection_state::invalid }
    {
    }

    db_connection::~db_connection()
    {
    }

    bool db_connection::start(db_loop *loop, const char *conninfo, void *data) noexcept
    {
        while (true) {
            _connection = PQconnectStart(conninfo);
            if (_connection == nullptr) {
                logerror("Can't allocate memory for pq connection struct.");
                break;
            }

            if (status() == ConnStatusType::CONNECTION_BAD) {
                logerror("Failed to create pq connection struct (%s).", PQerrorMessage(_connection));
                break;
            }

            int fd { PQsocket(_connection) };
            fd = fcntl(fd, F_DUPFD_CLOEXEC, 0);
            if (fd < 0) {
                logerror("Failed to dup fd (%s).", strerror(errno));
                break;
            }

            int status { uv_poll_init_socket(loop->get_loop(), &_handle.poll, fd) };
            if (status != 0) {
                logerror("Failed to init poll fd (%s).", uv_err_name(status));
                break;
            }

            uv_handle_set_data(&_handle.handle, data);
            set_state(connection_state::connecting);

            return true;
        }

        finish();

        return false;
    }

    void db_connection::finish() noexcept
    {
        stop_polling();

        if (_connection != nullptr) {
            PQfinish(_connection);
            _connection = nullptr;

            set_state(connection_state::invalid);
        }
    }

    bool db_connection::start_polling(int events, uv_poll_cb fn) noexcept
    {
        bool result { true };
        int status { uv_poll_start(&_handle.poll, events, fn) };
        if (status != 0) {
            logwarn("Failed to start poll connection (%s).", uv_err_name(status));
            result = false;
        }
        return result;
    }

    void db_connection::stop_polling() noexcept
    {
        if (uv_is_active(&_handle.handle)) {
            uv_poll_stop(&_handle.poll);
        }
    }

    PostgresPollingStatusType db_connection::poll() noexcept
    {
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

    ConnStatusType db_connection::status() const noexcept
    {
        return PQstatus(_connection);
    }

    PGresult *db_connection::result() noexcept
    {
        return PQgetResult(_connection);
    }

    const char *db_connection::error_message() const noexcept
    {
        return PQerrorMessage(_connection);
    }

    int db_connection::send_request(db_request *request) noexcept
    {
        request->assign_connection(this);

        return PQsendQueryParams(_connection,
                request->query(),
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
