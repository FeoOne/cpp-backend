/**
 * @file io_context.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ROCKET_IO_CONTEXT_H
#define ROCKET_IO_CONTEXT_H

#include "work/work_context.h"

namespace rocket {

    class io_context : public groot::crucial<work_context, io_context> {
    public:
        GR_DECLARE_SMARTPOINTERS(io_context)
        GR_DELETE_ALL_DEFAULT(io_context)

        explicit io_context(const groot::setting& config, task_router *router) noexcept;
        virtual ~io_context() = default;

    };

}

#endif /* ROCKET_IO_CONTEXT_H */
