/**
 * @file db_response_task.h
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#ifndef ROCKET_DB_RESPONSE_TASK_H
#define ROCKET_DB_RESPONSE_TASK_H

#include "task/basic_task.h"

namespace rocket {

    class db_response_task : public groot::crucial<basic_task, db_response_task> {
    public:
        GR_DECLARE_SMARTPOINTERS(db_response_task)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(db_response_task)

        explicit db_response_task(nullptr_t) noexcept {}
        virtual ~db_response_task() = default;

    private:

    };

}

#endif /* ROCKET_DB_RESPONSE_TASK_H */
