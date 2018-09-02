/**
 * @file system_context.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef ROCKET_SYSTEM_CONTEXT_H
#define ROCKET_SYSTEM_CONTEXT_H

#include "work/work_context.h"

namespace rocket {

    class system_context : public groot::crucial<work_context, system_context> {
    public:
        GR_DECLARE_SMARTPOINTERS(system_context)
        GR_DELETE_ALL_DEFAULT(system_context)

        explicit system_context(const groot::setting& config, task_router *router) noexcept;
        virtual ~system_context() = default;

    };

}

#endif /* ROCKET_SYSTEM_CONTEXT_H */
