/**
 * @file system_context.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef ENGINE_SYSTEM_CONTEXT_H
#define ENGINE_SYSTEM_CONTEXT_H

#include "work/work_context.h"

namespace engine {

    class system_context : public stl::crucial<work_context, system_context> {
    public:
        STL_DECLARE_SMARTPOINTERS(system_context)
        STL_DELETE_ALL_DEFAULT(system_context)

        explicit system_context(const stl::setting& config, task_router *router) noexcept;
        virtual ~system_context() = default;

    };

}

#endif /* ENGINE_SYSTEM_CONTEXT_H */
