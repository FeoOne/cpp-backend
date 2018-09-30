/**
 * @file worker_watchdog_service.h
 * @author Feo
 * @date 14/09/2018
 * @brief
 */

#ifndef ROCKET_WORKER_WATCHDOG_SERVICE_H
#define ROCKET_WORKER_WATCHDOG_SERVICE_H

#include "work/work_service.h"

namespace rocket {

    class worker_watchdog_service final : public groot::crucial<work_service, worker_watchdog_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(worker_watchdog_service)
        GR_DELETE_ALL_DEFAULT(worker_watchdog_service)

        explicit worker_watchdog_service(const groot::setting& config,
                                         task_router *router,
                                         const work_service_delegate *delegate) noexcept;
        virtual ~worker_watchdog_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_worker_broken_task(basic_task *t) noexcept;

    };

}

#endif /* ROCKET_WORKER_WATCHDOG_SERVICE_H */
