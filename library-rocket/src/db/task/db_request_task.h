/**
 * @file db_request_task.h
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#ifndef ROCKET_DB_REQUEST_TASK_H
#define ROCKET_DB_REQUEST_TASK_H

#include "task/task.h"

namespace rocket {

    class db_request_task : public groot::crucial<task, db_request_task> {
    public:
        GR_DECLARE_SMARTPOINTERS(db_request_task)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(db_request_task)

        explicit db_request_task(nullptr_t) noexcept {}
        virtual ~db_request_task() = default;

    private:

    };

}

#endif /* ROCKET_DB_REQUEST_TASK_H */
