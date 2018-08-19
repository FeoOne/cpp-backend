/**
 * @file webserver_context.h
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#ifndef ENGINE_WEBSERVER_CONTEXT_H
#define ENGINE_WEBSERVER_CONTEXT_H

#include "work/work_context.h"

#define EG_CONTEXT_CREATOR(context)                     \
    [](const framework::config_setting::sptr& config,   \
       const engine::task_router::sptr& router) {       \
        return context::make_unique(config, router);    \
    }

namespace engine {

    class webserver_context : public framework::crucial<work_context, webserver_context> {
    public:
        FW_DECLARE_SMARTPOINTERS(webserver_context)
        FW_DELETE_ALL_DEFAULT(webserver_context)

        explicit webserver_context(const framework::config_setting::sptr& config,
                                   const task_router::sptr& router) noexcept;
        virtual ~webserver_context();

        void setup() noexcept final;
        void reset() noexcept final;

    private:

    };

}

#endif /* ENGINE_WEBSERVER_CONTEXT_H */
