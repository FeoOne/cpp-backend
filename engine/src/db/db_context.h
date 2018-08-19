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

    class db_context : public framework::crucial<work_context, db_context> {
    public:
        FW_DECLARE_SMARTPOINTERS(db_context)
        FW_DELETE_ALL_DEFAULT(db_context)

        explicit db_context(const framework::config_setting::sptr& config,
                            const task_router::sptr& router) noexcept;
        virtual ~db_context();

        void setup() noexcept final;
        void reset() noexcept final;

    };

}

#endif /* ENGINE_DB_CONTEXT_H */