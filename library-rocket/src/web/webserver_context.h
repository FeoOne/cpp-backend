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

        explicit webserver_context(const groot::setting& config, task_router *router) noexcept;
        virtual ~webserver_context() = default;

    private:

    };

}

#endif /* ROCKET_WEBSERVER_CONTEXT_H */
