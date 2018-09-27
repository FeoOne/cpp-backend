//
// Created by Feo on 03/09/2018.
//

#include "context/db/core/db_connection.h"

namespace rocket {

    db_connection::db_connection() :
            _state { state::invalid },
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

            int fd = PQsocket(_connection);
            fd = fcntl(fd, F_DUPFD_CLOEXEC, 0);
            if (fd < 0) {
                logerror("Failed to dup fd (%s).", strerror(errno));
                break;
            }

            int status = uv_poll_init(loop->get_loop(), &_handle, fd);
            if (status != 0) {
                logerror("Failed to poll fd (%s).", uv_err_name(status));
                break;
            }

            _handle.data = this;

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

    void db_connection::poll() noexcept
    {
        int status { 0 };
        int events { 0 };

        switch (_state) {
            case state::connecting: {
                status = PQconnectPoll(_connection);
                break;
            }
            case state::resetting: {
                status = PQresetPoll(_connection);
                break;
            }
            default: {
                logwarn("Unexpected state %d.", static_cast<int>(_state));
                return;
            }
        }

        switch (status) {
            case PGRES_POLLING_READING: {
                events = UV_READABLE;
                // todo: cb
                break;
            }
            case PGRES_POLLING_WRITING: {
                events = UV_WRITABLE;
                // todo: cb
                break;
            }
            case PGRES_POLLING_OK: {
                _state = state::available;
                events = UV_READABLE | UV_WRITABLE;
                // todo: cb
                break;
            }
            case PGRES_POLLING_FAILED: {
                switch (_state) {
                    case state::connecting: {
                        _state = state::bad_connect;
                        break;
                    }
                    case state::resetting: {
                        _state = state::bad_reset;
                        break;
                    }
                    default: {
                        logwarn("Unexpected state %d.", static_cast<int>(_state));
                        return;
                    }
                }
                // todo: reconnect timer
                return;
            }
            default: {
                logwarn("Unexpected poll status %d.", status);
                return;
            }
        }

        //status = uv_poll_start(&_handle, events, );
    }

}
