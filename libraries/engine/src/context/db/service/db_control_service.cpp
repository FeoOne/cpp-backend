/**
 * @file db_control_service.cpp
 * @author Feo
 * @date 09/11/2018
 * @brief
 */

#include "context/db/core/db_response.h"
#include "context/db/task/db_request_task.h"
#include "context/db/task/db_response_task.h"

#include "context/db/service/db_control_service.h"

#define EX_DEFAULT_MAX_CONNECTION_COUNT 4
#define EX_DEFAULT_CONNECT_INTERVAL     1000

namespace engine {

    db_control_service::db_control_service(const stl::setting& config,
                                           task_router *router,
                                           const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _conninfo {},
            _max_connection_count { 0 },
            _connect_interval { 0 },
            _reconnect_timer {},
            _connections {},
            _available_connections {},
            _unavailable_connections {},
            _connections_by_handle {},
            _active_requests {}
    {
        EX_ASSIGN_TASK_HANDLER(db_request_task, db_control_service, handle_db_request_task);
    }

    // virtual
    db_control_service::~db_control_service()
    {
    }

    // virtual
    void db_control_service::setup() noexcept
    {
        setup_connections();
        setup_reconnect_timer();
    }

    // virtual
    void db_control_service::reset() noexcept
    {
        reset_reconnect_timer();
        reset_connections();
    }

    void db_control_service::setup_connections() noexcept
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

        while (_connections.size() < _max_connection_count) {
            auto connection { new (std::nothrow) db_connection };

            _connections.push_back(connection);
            _unavailable_connections.push_back(connection);
            _connections_by_handle[connection->handle()] = connection;
        }
    }

    void db_control_service::reset_connections() noexcept
    {

    }

    void db_control_service::setup_reconnect_timer() noexcept
    {
        int status { uv_timer_init(delegate()->loop<db_loop>()->get_loop(), &_reconnect_timer.timer) };
        if (status != 0) {
            logerror("Failed to set up connect timer (%s).", uv_strerror(status));
            return;
        }

        uv_handle_set_data(&_reconnect_timer.handle, this);

        start_reconnect_timer();
    }

    void db_control_service::reset_reconnect_timer() noexcept
    {
        stop_reconnect_timer();
    }

    void db_control_service::start_reconnect_timer() noexcept
    {
        if (uv_is_active(&_reconnect_timer.handle)) {
            return;
        }

        int status { uv_timer_start(&_reconnect_timer.timer,
                                    &db_control_service::reconnect_timer_callback,
                                    _connect_interval,
                                    _connect_interval) };
        logassert(status == 0, "Failed to start reconnect timer (%s).", uv_strerror(status));
    }

    void db_control_service::stop_reconnect_timer() noexcept
    {
        if (!uv_is_active(&_reconnect_timer.handle)) {
            return;
        }

        int status { uv_timer_stop(&_reconnect_timer.timer) };
        logassert(status == 0, "Failed to stop reconnect timer (%s).", uv_strerror(status));
    }

    void db_control_service::poll_connection(db_connection *connection) noexcept
    {
        int events { 0 };
        int status { connection->poll() };

        switch (status) {
            case PostgresPollingStatusType::PGRES_POLLING_READING: {
                events = uv_poll_event::UV_READABLE;
                break;
            }
            case PostgresPollingStatusType::PGRES_POLLING_WRITING: {
                events = uv_poll_event::UV_WRITABLE;
                break;
            }
            case PostgresPollingStatusType::PGRES_POLLING_OK: {
                connection->set_state(db_connection::connection_state::available);
                _available_connections.push(connection);
                check_pending_requests();
                return;
            }
            default: {
                logwarn("Poll failed %d. %s", status, connection->error_message());
                finish_connection(connection);
                return;
            }
        }

        if (!connection->start_polling(events, &db_control_service::connect_poll_callback)) {
            finish_connection(connection);
        }
    }

    void db_control_service::finish_connection(db_connection *connection) noexcept
    {
        connection->finish();
        _unavailable_connections.push_back(connection);
        start_reconnect_timer();
    }

    void db_control_service::handle_db_request_task(basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<db_request_task *>(base_task) };
        add_request(task->request());
    }

    void db_control_service::check_pending_requests() noexcept
    {
        if (!_available_connections.empty() && !_pending_requests.empty()) {
            auto connection { _available_connections.front() };
            _available_connections.pop();

            auto request { _pending_requests.front() };

            auto status { connection->send_request(request) };
            if (status != 1) {
                finish_connection(connection);
                request->refresh();
                return;
            }

            if (!connection->start_polling(uv_poll_event::UV_READABLE, &db_control_service::request_poll_callback)) {
                finish_connection(connection);
                request->refresh();
                return;
            }

            _pending_requests.pop();
            _active_requests[connection->handle()] = request;

            connection->flush();
        }
    }

    void db_control_service::add_request(db_request *request) noexcept
    {
        request->refresh();
        _pending_requests.push(request);
        check_pending_requests();
    }

    void db_control_service::on_reconnect_timer() noexcept
    {
        logdebug("Reconnect timer.");
        auto it { _unavailable_connections.begin() };
        while (it != _unavailable_connections.end()) {
            auto connection { *it };
            if (connection->start(delegate()->loop<db_loop>(), _conninfo, this)) {
                poll_connection(connection);

                if (connection->state() != db_connection::connection_state::invalid) {
                    it = _unavailable_connections.erase(it);
                    continue;
                }
            }

            ++it;
        }

        if (_unavailable_connections.empty()) {
            stop_reconnect_timer();
        }
    }

    void db_control_service::on_connect_poll(poll_handle *handle, int status, int events) noexcept
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
        connection->stop_polling();

        poll_connection(connection);
    }

    void db_control_service::on_request_poll(poll_handle *handle, int status, int events) noexcept
    {
        if (status < 0) {
            logerror("Polling query error (%s).", uv_err_name(status));
            return;
        }

        if ((events & uv_poll_event::UV_READABLE) != uv_poll_event::UV_READABLE) {
            logwarn("Polling query error.");
            return;
        }

        auto request { _active_requests[handle] };
        auto connection { request->connection() };

        if (connection->consume_input() == 0) {
            add_request(request);
            finish_connection(connection);
            return;
        }

        PGnotify *notify;
        while ((notify = connection->notifies()) != nullptr) {
            lognotice("Notify of '%s' received from backend PID %d\n", notify->relname, notify->be_pid);
            PQfreemem(notify);
        }

        if (connection->is_busy()) {
            return;
        }

        db_response response { connection->result() };
        if (!response.is_valid() || response.status() == PGRES_FATAL_ERROR) {
            // todo: process error
            logwarn("Request error: %s", response.result_error_message());
            finish_connection(connection);
            return;
        }

        request->process_response(&response);

        connection->stop_polling();

        auto it { _active_requests.find(connection->handle()) };
        if (it != _active_requests.end()) {
            _active_requests.erase(it);
        }

        auto result { connection->result() };
        while (result != nullptr) {
            PQclear(result);
            result = connection->result();
        }

        if (response.is_valid() && request->is_callable()) {
            auto task { basic_task::create<db_response_task>(request) };
            router()->enqueue(task);
        }

        finish_connection(connection);
    }

    // static
    void db_control_service::reconnect_timer_callback(uv_timer_t *timer) noexcept
    {
        if (timer != nullptr && timer->data != nullptr) {
            static_cast<db_control_service *>(timer->data)->on_reconnect_timer();
        }
    }

    // static
    void db_control_service::connect_poll_callback(uv_poll_t* handle, int status, int events) noexcept
    {
        if (handle != nullptr && handle->data != nullptr) {
            static_cast<db_control_service *>(handle->data)->on_connect_poll(reinterpret_cast<poll_handle *>(handle),
                                                                             status,
                                                                             events);
        }
    }

    // static
    void db_control_service::request_poll_callback(uv_poll_t* handle, int status, int events) noexcept
    {
        if (handle != nullptr && handle->data != nullptr) {
            static_cast<db_control_service *>(handle->data)->on_request_poll(reinterpret_cast<poll_handle *>(handle),
                                                                             status,
                                                                             events);
        }
    }

}
