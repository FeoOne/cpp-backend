/**
 * @file udp_service.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ROCKET_UDP_SERVICE_H
#define ROCKET_UDP_SERVICE_H

#include "work/work_service.h"

namespace rocket {

    class udp_service final : public groot::crucial<work_service, udp_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(udp_service)
        GR_DELETE_ALL_DEFAULT(udp_service)

        explicit udp_service(const groot::setting& config,
                             task_router *router,
                             const work_service_delegate *delegate) noexcept;
        virtual ~udp_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:

    };

}

#endif /* ROCKET_UDP_SERVICE_H */
