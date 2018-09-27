/**
 * @file tcp_heartbeat_service.h
 * @author Feo
 * @date 27/09/2018
 * @brief
 */

#ifndef ROCKET_TCP_HEARTBEAT_SERVICE_H
#define ROCKET_TCP_HEARTBEAT_SERVICE_H

#include "work/work_service.h"

namespace rocket {

    class tcp_heartbeat_service final : public groot::crucial<work_service, tcp_heartbeat_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(tcp_heartbeat_service)
        GR_DELETE_ALL_DEFAULT(tcp_heartbeat_service)

        explicit tcp_heartbeat_service(const groot::setting& config,
                                       task_router *router,
                                       const work_service_delegate *service_delegate) noexcept;
        virtual ~tcp_heartbeat_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:

    };

}

#endif /* ROCKET_TCP_HEARTBEAT_SERVICE_H */
