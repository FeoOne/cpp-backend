/**
 * @file message_distribution_service.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ROCKET_MESSAGE_DISTRIBUTION_SERVICE_H
#define ROCKET_MESSAGE_DISTRIBUTION_SERVICE_H

#include "work/work_service.h"

namespace rocket {

    class message_filter_service final : public groot::crucial<work_service, message_filter_service> {
    public:
        FW_DECLARE_SMARTPOINTERS(message_filter_service)
        FW_DELETE_ALL_DEFAULT(message_filter_service)

        explicit message_filter_service(const groot::config_setting::sptr& config,
                                        const task_router::sptr& router,
                                        const work_context_delegate *service_provider) noexcept;
        virtual ~message_filter_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_outgoing_packet_task(const rocket::task::sptr& t) noexcept;

    };

}

#endif /* PROJECT_MESSAGE_DISTRIBUTION_SERVICE_H */
