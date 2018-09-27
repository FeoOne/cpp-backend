/**
 * @file db_context.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ROCKET_DB_CONTEXT_H
#define ROCKET_DB_CONTEXT_H

#include "work/work_context.h"

namespace rocket {

    class db_context : public groot::crucial<work_context, db_context> {
    public:
        GR_DECLARE_SMARTPOINTERS(db_context)
        GR_DELETE_ALL_DEFAULT(db_context)

        explicit db_context(const groot::setting& config, task_router *router) noexcept;
        virtual ~db_context() = default;

    };

}

#endif /* ROCKET_DB_CONTEXT_H */
