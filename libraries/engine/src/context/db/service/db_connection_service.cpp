//
// Created by Feo on 07/09/2018.
//

#include "context/db/service/db_connection_service.h"

#define EX_DEFAULT_MAX_CONNECTION_COUNT 4
#define EX_DEFAULT_CONNECT_INTERVAL     1000

namespace engine {

    db_connection_service::db_connection_service(const stl::setting& config,
                                           task_router *router,
                                           const work_service_delegate *delegate) noexcept:
            crucial(config, router, delegate),
            _connections {},
            _available_connections {},
            _conninfo { nullptr },
            _max_connection_count { 0 },
            _connect_interval { 0 },
            _connect_timer {}
    {
        _connections.reserve(_max_connection_count);
    }

    // virtual
    db_connection_service::~db_connection_service()
    {
    }

    // virtual
    void db_connection_service::setup() noexcept
    {
        read_config();

        setup_connections();
        setup_connect_timer();
    }

    // virtual
    void db_connection_service::reset() noexcept
    {
        reset_connect_timer();
        reset_connections();
    }

    db_connection *db_connection_service::acquire_connection() noexcept
    {
        db_connection *result { nullptr };
        if (!_available_connections.empty()) {
            result = _available_connections.front();
            _available_connections.pop_front();
        }
        return result;
    }

    void db_connection_service::return_connection(db_connection *connection) noexcept
    {

    }

    void db_connection_service::read_config() noexcept
    {
        // conninfo
        if (!config().lookup_string(consts::config::key::CONNINFO, &_conninfo)) {
            logemerg("Can't setup db connection service: no '%s' presented.", consts::config::key::CONNINFO.data());
        }

        // max connection count
        config().lookup_int32<size_t>(consts::config::key::MAX_CONNECTION_COUNT,
                                          &_max_connection_count,
                                          EX_DEFAULT_MAX_CONNECTION_COUNT);

        // connect interval
        config().lookup_int64<u64>(consts::config::key::CONNECT_INTERVAL,
                                       &_connect_interval,
                                       EX_DEFAULT_CONNECT_INTERVAL);
    }

    void db_connection_service::setup_connections() noexcept
    {
        while (_connections.size() < _max_connection_count) {
            auto connection { db_connection::make_unique() };
            connection->start(delegate()->loop<db_loop>(), _conninfo);
            uv_handle_set_data(&connection->handle()->handle, this);
            _connections_by_handle[connection->handle()] = connection.get();
            poll(connection.get());
            _connections.push_back(std::move(connection));
        }
    }

    void db_connection_service::reset_connections() noexcept
    {
        while (!_connections.empty()) {
            _connections.back()->finish();
            _connections.pop_back();
        }
    }

    void db_connection_service::setup_connect_timer() noexcept
    {
        int status = uv_timer_init(delegate()->loop<db_loop>()->get_loop(), &_connect_timer);
        if (status != 0) {
            logerror("Failed to set up connect timer (%s).", uv_strerror(status));
            return;
        }

        _connect_timer.data = this;

        status = uv_timer_start(&_connect_timer,
                                &db_connection_service::connect_timer_callback,
                                _connect_interval,
                                _connect_interval);
        if (status != 0) {
            logerror("Failed to start connect timer (%s).", uv_strerror(status));
        }
    }

    void db_connection_service::reset_connect_timer() noexcept
    {
        int status = uv_timer_stop(&_connect_timer);
        if (status != 0) {
            logerror("Failed to stop connect timer (%s).", uv_strerror(status));
        }
    }

    void db_connection_service::on_connect_timer() noexcept
    {

    }

    void db_connection_service::poll(db_connection *connection) noexcept
    {
        int status { connection->poll() };
        int events { 0 };

        switch (status) {
            case PGRES_POLLING_READING: {
                events = uv_poll_event::UV_READABLE;
                break;
            }
            case PGRES_POLLING_WRITING: {
                events = uv_poll_event::UV_WRITABLE;
                break;
            }
            case PGRES_POLLING_OK: {
                connection->status(db_connection::state::available);
                _available_connections.push_back(connection);
                lognotice("Available connection %p.", connection);
                // todo: available connection
                return;
            }
            case PGRES_POLLING_FAILED: {
                connection->status(db_connection::state::invalid);
                logwarn("Failed to poll connection: %s", connection->error_message());
                auto it = std::find(_available_connections.begin(), _available_connections.end(), connection);
                if (it != _available_connections.end()) {
                    _available_connections.erase(it);
                }
                // todo: reconnect timer
                return;
            }
            default: {
                logwarn("Unexpected poll status %d. %s", status, connection->error_message());
                return;
            }
        }

        status = uv_poll_start(&connection->handle()->poll, events, &db_connection_service::poll_fn);
        if (status != 0) {
            logwarn("Failed to start poll connection.");
            connection->status(db_connection::state::invalid);
            // todo: reconnect timer
        }
    }

    void db_connection_service::on_poll(poll_handle* handle, int status, int events) noexcept
    {
        if (status < 0) {
            logerror("Polling error.");
            return;
        }

        if ((events & uv_poll_event::UV_READABLE) != uv_poll_event::UV_READABLE &&
                (events & uv_poll_event::UV_WRITABLE) != uv_poll_event::UV_WRITABLE) {
            logwarn("Polling error.");
            return;
        }

        auto connection { _connections_by_handle[handle] };
        uv_poll_stop(&handle->poll);

        poll(connection);
    }

    // static
    void db_connection_service::connect_timer_callback(uv_timer_t *timer) noexcept
    {
        if (timer != nullptr && timer->data != nullptr) {
            static_cast<db_connection_service *>(timer->data)->on_connect_timer();
        }
    }

    //static
    void db_connection_service::poll_fn(uv_poll_t* handle, int status, int events) noexcept
    {
        if (handle != nullptr && handle->data != nullptr) {
            static_cast<db_connection_service *>(handle->data)->on_poll(reinterpret_cast<poll_handle *>(handle),
                                                                        status,
                                                                        events);
        }
    }

}
