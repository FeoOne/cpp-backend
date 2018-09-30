//
// Created by Feo on 07/09/2018.
//

#ifndef ROCKET_CONNECTION_SERVICE_H
#define ROCKET_CONNECTION_SERVICE_H

#include "work/work_service.h"
#include "context/db/core/db_connection.h"

namespace rocket {

    class connection_service final : public groot::crucial<work_service, connection_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(connection_service)
        GR_DELETE_ALL_DEFAULT(connection_service)

        explicit connection_service(const groot::setting& config,
                                    task_router *router,
                                    const work_service_delegate *delegate) noexcept;
        virtual ~connection_service();

        void setup() noexcept final;
        void reset() noexcept final;

        db_connection *acquire_connection() noexcept;
        void release_connection(db_connection *connection) noexcept;

    private:
        std::vector<db_connection::uptr>    _connections;
        std::queue<db_connection *>         _available_connections;
        const char *                        _conninfo;
        size_t                              _max_connection_count;
        u64                                 _connect_interval;
        uv_timer_t                          _connect_timer;

        void read_config() noexcept;

        void setup_connections() noexcept;
        void reset_connections() noexcept;

        void setup_connect_timer() noexcept;
        void reset_connect_timer() noexcept;

        void on_connect_timer() noexcept;

        static void connect_timer_callback(uv_timer_t *timer) noexcept;

    };

}

#endif /* ROCKET_CONNECTION_SERVICE_H */
