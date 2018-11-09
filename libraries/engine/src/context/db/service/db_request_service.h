/**
 * @file db_request_service.h
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#ifndef ENGINE_DB_REQUEST_SERVICE_H
#define ENGINE_DB_REQUEST_SERVICE_H

#include "work/service/work_service.h"
#include "context/db/core/db_request.h"

namespace engine {

    class db_request_service final : public stl::crucial<work_service, db_request_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(db_request_service)
        STL_DELETE_ALL_DEFAULT(db_request_service)

        explicit db_request_service(const stl::setting& config,
                                 task_router *router,
                                 const work_service_delegate *delegate) noexcept;
        virtual ~db_request_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        std::queue<db_request *>                            _pending_requests;
        std::unordered_map<poll_handle *, db_request *>     _active_requests;

        void handle_db_request_task(basic_task *task) noexcept;

        void on_query(poll_handle* handle, int status, int events) noexcept;
        static void query_fn(uv_poll_t* handle, int status, int events) noexcept;

    };

}

#endif /* PROJECT_DB_REQUEST_SERVICE_H */
