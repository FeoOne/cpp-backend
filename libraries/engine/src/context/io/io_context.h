/**
 * @file io_context.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ENGINE_IO_CONTEXT_H
#define ENGINE_IO_CONTEXT_H

#include "work/work_context.h"

namespace engine {

    class io_context : public stl::crucial<work_context, io_context> {
    public:
        STL_DECLARE_SMARTPOINTERS(io_context)
        STL_DELETE_ALL_DEFAULT(io_context)

        explicit io_context(const stl::setting& config, task_router *router) noexcept;
        virtual ~io_context() = default;

    };

}

#endif /* ENGINE_IO_CONTEXT_H */
