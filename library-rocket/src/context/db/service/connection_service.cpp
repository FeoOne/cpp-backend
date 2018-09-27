//
// Created by Feo on 07/09/2018.
//

#include "context/db/service/connection_service.h"

#define RC_DEFAULT_MAX_CONNECTION_COUNT 4
#define RC_DEFAULT_CONNECT_INTERVAL     1000

namespace rocket {

    connection_service::connection_service(const groot::setting& config,
                                           task_router *router,
                                           const work_service_delegate *service_delegate) noexcept:
            crucial(config, router, service_delegate),
            _connections {},
            _available_connections {},
            _conninfo { nullptr },
            _max_connection_count { 0 },
            _connect_interval { 0 },
            _connect_timer {}
    {
        read_config();

        _connections.reserve(_max_connection_count);
    }

    // virtual
    connection_service::~connection_service()
    {
    }

    // virtual
    void connection_service::setup() noexcept
    {
        setup_connections();
        setup_connect_timer();
    }

    // virtual
    void connection_service::reset() noexcept
    {
        reset_connect_timer();
        reset_connections();
    }

    db_connection *connection_service::acquire_connection() noexcept
    {
        return nullptr;
    }

    void connection_service::release_connection(db_connection *connection) noexcept
    {

    }

    void connection_service::read_config() noexcept
    {
        // conninfo
        if (!config().lookup_string(consts::config::key::CONNINFO, &_conninfo)) {
            logemerg("Can't setup db connection service: no '%s' presented.", consts::config::key::CONNINFO.data());
        }

        // max connection count
        config().lookup_int32<size_t>(consts::config::key::MAX_CONNECTION_COUNT,
                                          &_max_connection_count,
                                          RC_DEFAULT_MAX_CONNECTION_COUNT);

        // connect interval
        config().lookup_int64<u64>(consts::config::key::CONNECT_INTERVAL,
                                       &_connect_interval,
                                       RC_DEFAULT_CONNECT_INTERVAL);
    }

    void connection_service::setup_connections() noexcept
    {
        for (size_t i = 0; i < _max_connection_count; ++i) {
            auto connection { db_connection::make_unique() };
            connection->start(delegate()->get_loop<db_loop>(), _conninfo);
            //_connections.push_back(connection);
        }
    }

    void connection_service::reset_connections() noexcept
    {
        _connections.clear();
    }

    void connection_service::setup_connect_timer() noexcept
    {
        int status = uv_timer_init(delegate()->get_loop<db_loop>()->get_loop(), &_connect_timer);
        if (status != 0) {
            logerror("Failed to set up connect timer (%s).", uv_strerror(status));
            return;
        }

        _connect_timer.data = this;

        status = uv_timer_start(&_connect_timer,
                                &connection_service::connect_timer_routine,
                                _connect_interval,
                                _connect_interval);
        if (status != 0) {
            logerror("Failed to start connect timer (%s).", uv_strerror(status));
        }
    }

    void connection_service::reset_connect_timer() noexcept
    {
        int status = uv_timer_stop(&_connect_timer);
        if (status != 0) {
            logerror("Failed to stop connect timer (%s).", uv_strerror(status));
        }
    }

    void connection_service::on_connect_timer() noexcept
    {

    }

    // static
    void connection_service::connect_timer_routine(uv_timer_t *timer) noexcept
    {
        if (timer != nullptr && timer->data != nullptr) {
            static_cast<connection_service *>(timer->data)->on_connect_timer();
        }
    }

}
