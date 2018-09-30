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

    class udp_service final : public stl::crucial<work_service, udp_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(udp_service)
        STL_DELETE_ALL_DEFAULT(udp_service)

        explicit udp_service(const stl::setting& config,
                             task_router *router,
                             const work_service_delegate *delegate) noexcept;
        virtual ~udp_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:

    };

}

#endif /* ENGINE_UDP_SERVICE_H */
