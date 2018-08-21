/**
 * @file udp_service.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ENGINE_UDP_SERVICE_H
#define ENGINE_UDP_SERVICE_H

#include "work/work_service.h"

namespace engine {

    class udp_service final : public framework::crucial<work_service, udp_service> {
    public:
        FW_DECLARE_SMARTPOINTERS(udp_service)
        FW_DELETE_ALL_DEFAULT(udp_service)

        explicit udp_service(const framework::config_setting::sptr& config,
                             const task_router::sptr& router,
                             const work_context_delegate *service_provider) noexcept;
        virtual ~udp_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:

    };

}

#endif /* ENGINE_UDP_SERVICE_H */
