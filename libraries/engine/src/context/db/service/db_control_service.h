/**
 * @file db_control_service.h
 * @author Feo
 * @date 09/11/2018
 * @brief
 */

#ifndef ENGINE_DB_CONTROL_SERVICE_H
#define ENGINE_DB_CONTROL_SERVICE_H

#include "work/service/work_service.h"
#include "context/db/core/db_request.h"
#include "context/db/core/db_connection.h"

namespace engine {

    class db_control_service final : public stl::crucial<work_service, db_control_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(db_control_service)
        STL_DELETE_ALL_DEFAULT(db_control_service)

        explicit db_control_service(const stl::setting& config,
                                    task_router *router,
                                    const work_service_delegate *delegate) noexcept;

        virtual ~db_control_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        const char *                                        _conninfo;
        size_t                                              _max_connection_count;
        u64                                                 _connect_interval;

        timer_handle                                        _reconnect_timer;

        std::vector<db_connection *>                        _connections;
        std::queue<db_connection *>                         _available_connections;
        std::list<db_connection *>                          _unavailable_connections;
        std::unordered_map<poll_handle *, db_connection *>  _connections_by_handle;

        std::queue<db_request *>                            _pending_requests;
        std::unordered_map<poll_handle *, db_request *>     _active_requests;

        void setup_connections() noexcept;
        void reset_connections() noexcept;

        void setup_reconnect_timer() noexcept;
        void reset_reconnect_timer() noexcept;
        void start_reconnect_timer() noexcept;
        void stop_reconnect_timer() noexcept;

        void poll_connection(db_connection *connection) noexcept;
        void finish_connection(db_connection *connection) noexcept;

        void handle_db_request_task(basic_task *base_task) noexcept;

        void check_pending_requests() noexcept;
        void add_request(db_request *request) noexcept;

        void on_reconnect_timer() noexcept;
        void on_connect_poll(poll_handle *handle, int status, int events) noexcept;
        void on_request_poll(poll_handle *handle, int status, int events) noexcept;

        static void reconnect_timer_callback(uv_timer_t *timer) noexcept;
        static void connect_poll_callback(uv_poll_t* handle, int status, int events) noexcept;
        static void request_poll_callback(uv_poll_t* handle, int status, int events) noexcept;

    };

}

#endif /* ENGINE_DB_CONTROL_SERVICE_H */
