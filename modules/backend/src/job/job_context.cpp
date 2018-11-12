/**
 * @file job_context.cpp
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#include "job/service/io_service.h"
#include "job/service/ws_service.h"
#include "job/service/session_service.h"
#include "job/service/bitcoin_rpc_service.h"
#include "job/service/message/database_messaging_service.h"
#include "job/service/message/manbtc_messaging_service.h"

#include "job/job_context.h"

namespace backend {

    job_context::job_context(const stl::setting& config, engine::task_router *router) noexcept :
            engine::job_context(config, router)
    {
        add_service(io_service::make_unique(config, router, this));
        add_service(ws_service::make_unique(config, router, this));
        add_service(session_service::make_unique(config, router, this));
        add_service(database_messaging_service::make_unique(config, router, this));
        add_service(manbtc_messaging_service::make_unique(config, router, this));
        add_service(bitcoin_rpc_service::make_unique(config, router, this));

        EX_BIND_TASK_ROUTE(engine::io_request_task, io_service);
        EX_BIND_TASK_ROUTE(engine::connection_status_changed_task, io_service);
        EX_BIND_TASK_ROUTE(engine::ws_request_task, ws_service);
    }

}
