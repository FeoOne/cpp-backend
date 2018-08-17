/**
 * @file webserver_context.h
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#ifndef ENGINE_WEBSERVER_CONTEXT_H
#define ENGINE_WEBSERVER_CONTEXT_H

#include "work/work_context.h"

namespace engine {

    class webserver_context : public framework::crucial<work_context, webserver_context> {
    public:
        FW_DECLARE_SMARTPOINTERS(webserver_context)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(webserver_context)

        explicit webserver_context(const framework::config_setting::sptr& config,
                                   const task_router::sptr& router) noexcept;
        virtual ~webserver_context() = default;

    private:

    };

}

#endif /* ENGINE_WEBSERVER_CONTEXT_H */
