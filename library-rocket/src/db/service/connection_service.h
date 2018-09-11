//
// Created by Feo on 07/09/2018.
//

#ifndef ROCKET_CONNECTION_SERVICE_H
#define ROCKET_CONNECTION_SERVICE_H

#include "work/work_service.h"
#include "db/connection/db_connection.h"

namespace rocket {

    class connection_service final : public groot::crucial<work_service, connection_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(connection_service)
        GR_DELETE_ALL_DEFAULT(connection_service)

        explicit connection_service(const groot::setting& config,
                                    task_router *router,
                                    const work_service_delegate *service_delegate) noexcept;
        virtual ~connection_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        groot::fixed_memory_pool::uptr      _connection_pool;

    };

}

#endif /* ROCKET_CONNECTION_SERVICE_H */
