/**
 * @file webserver_context.h
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#ifndef ROCKET_WEBSERVER_CONTEXT_H
#define ROCKET_WEBSERVER_CONTEXT_H

#include "work/work_context.h"

namespace rocket {

    class webserver_context : public groot::crucial<work_context, webserver_context> {
    public:
        GR_DECLARE_SMARTPOINTERS(webserver_context)
        GR_DELETE_ALL_DEFAULT(webserver_context)

        explicit webserver_context(const groot::config_setting::sptr& config,
                                   const task_router::sptr& router) noexcept;
        virtual ~webserver_context();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        const bool      _websocket_service_enabled;

    };

}

#endif /* ROCKET_WEBSERVER_CONTEXT_H */
