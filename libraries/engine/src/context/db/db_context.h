/**
 * @file db_context.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ENGINE_DB_CONTEXT_H
#define ENGINE_DB_CONTEXT_H

#include "work/work_context.h"

namespace engine {

    class db_context : public stl::crucial<work_context, db_context> {
    public:
        STL_DECLARE_SMARTPOINTERS(db_context)
        STL_DELETE_ALL_DEFAULT(db_context)

        explicit db_context(const stl::setting& config, task_router *router) noexcept;
        virtual ~db_context() = default;

    };

}

#endif /* ENGINE_DB_CONTEXT_H */
