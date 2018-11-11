/**
 * @file web_context.h
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#ifndef ENGINE_WEBSERVER_CONTEXT_H
#define ENGINE_WEBSERVER_CONTEXT_H

#include "work/work_context.h"

namespace engine {

    class web_context : public stl::crucial<work_context, web_context> {
    public:
        STL_DECLARE_SMARTPOINTERS(web_context)
        STL_DELETE_ALL_DEFAULT(web_context)

        explicit web_context(const stl::setting& config, task_router *router) noexcept;
        virtual ~web_context() = default;

    private:

    };

}

#endif /* ENGINE_WEBSERVER_CONTEXT_H */
