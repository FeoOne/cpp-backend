//
// Created by Feo on 07/09/2018.
//

#include "db/service/connection_service.h"

namespace rocket {

    connection_service::connection_service(const groot::setting& config,
                                           task_router *router,
                                           const work_service_delegate *service_delegate) noexcept:
            crucial(config, router, service_delegate),
            _connections {},
            _available_connections {},
            _conninfo { nullptr },
            _max_connection_count { 0 }
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
        for (size_t i = 0; i < _max_connection_count; ++i) {
            auto connection { db_connection::make_unique() };
            _connections.push_back(connection);
        }
    }

    // virtual
    void connection_service::reset() noexcept
    {

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
        if (!get_config().lookup_string(consts::CONFIG_KEY_CONNINFO, &_conninfo)) {
            logemerg("Can't setup db connection service: no 'conninfo' presented.");
        }

        // max connection count
        get_config().lookup_int32(consts::CONFIG_KEY_MAX_CONNECTION_COUNT,
                                  &_max_connection_count,
                                  consts::DB_DEFAULT_MAX_CONNECTION_COUNT);
    }

}
