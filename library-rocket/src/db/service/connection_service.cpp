//
// Created by Feo on 07/09/2018.
//

#include "db/service/connection_service.h"

#define RC_CONNECTION_POOL_SIZE 10240

namespace rocket {

    connection_service::connection_service(const groot::setting& config,
                                           task_router *router,
                                           const work_service_delegate *service_delegate) noexcept:
            crucial(config, router, service_delegate),
            _connection_pool { groot::fixed_memory_pool::make_unique(sizeof(db_connection), RC_CONNECTION_POOL_SIZE) }
    {
    }

    // virtual
    connection_service::~connection_service()
    {
    }

    // virtual
    void connection_service::setup() noexcept
    {

    }

    // virtual
    void connection_service::reset() noexcept
    {

    }

}
