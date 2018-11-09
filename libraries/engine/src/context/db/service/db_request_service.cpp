/**
 * @file db_request_service.cpp
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#include "context/db/task/db_request_task.h"
#include "context/db/service/db_connection_service.h"

#include "context/db/service/db_request_service.h"

namespace engine {

    db_request_service::db_request_service(const stl::setting& config,
                                           task_router *router,
                                           const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _pending_requests {},
            _active_requests {}
    {
        EX_ASSIGN_TASK_HANDLER(db_request_task, db_request_service, handle_db_request_task);
    }

    // virtual
    db_request_service::~db_request_service()
    {

    }

    // virtual
    void db_request_service::setup() noexcept
    {

    }

    // virtual
    void db_request_service::reset() noexcept
    {

    }

    void db_request_service::handle_db_request_task(basic_task *base_task) noexcept
    {
        auto task { reinterpret_cast<db_request_task *>(base_task) };
        auto service { delegate()->service<db_connection_service>() };
        auto connection { service->acquire_connection() };
        if (connection == nullptr) {
            _pending_requests.push(task->request());
        } else {
            auto status { connection->send_query(task->request()) };
            if (status != 0) {
                // todo: reset connection
            }

            status = uv_poll_start(&connection->handle()->poll,
                    uv_poll_event::UV_READABLE,
                    &db_request_service::query_fn);
            if (status != 0) {
                logwarn("Failed to start poll connection.");
                // todo: reset connection
            }

            _active_requests[connection->handle()] = task->request();

            connection->flush();
        }
    }

    void db_request_service::on_query(poll_handle* handle, int status, int events) noexcept
    {
        if (status < 0) {
            logerror("Polling query error.");
            return;
        }

        if ((events & uv_poll_event::UV_READABLE) != uv_poll_event::UV_READABLE) {
            logwarn("Polling query error.");
            return;
        }

        auto request { _active_requests[handle] };
        auto connection { request->connection() };

        if (connection->consume_input() == 0) {
            // todo: error
        }

        PGnotify *notify;
        while ((notify = connection->notifies()) != nullptr) {
            lognotice("Notify of '%s' received from backend PID %d\n", notify->relname, notify->be_pid);
            PQfreemem(notify);
        }

        if (!connection->is_busy()) {

        }
    }

    // static
    void db_request_service::query_fn(uv_poll_t* handle, int status, int events) noexcept
    {
        // warning: handle->data point on db_connection_service
        if (handle != nullptr && handle->data != nullptr) {
            static_cast<db_request_service *>(handle->data)->on_query(reinterpret_cast<poll_handle *>(handle),
                                                                      status,
                                                                      events);
        }
    }

}
