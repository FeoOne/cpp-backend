/**
 * @file web_context.h
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#ifndef ROCKET_WEBSERVER_CONTEXT_H
#define ROCKET_WEBSERVER_CONTEXT_H

#include "work/work_context.h"

namespace rocket {

    class web_context : public groot::crucial<work_context, web_context> {
    public:
        GR_DECLARE_SMARTPOINTERS(web_context)
        GR_DELETE_ALL_DEFAULT(web_context)

        explicit web_context(const groot::setting& config, task_router *router) noexcept;
        virtual ~web_context() = default;

    private:

    };

}

#endif /* ROCKET_WEBSERVER_CONTEXT_H */
