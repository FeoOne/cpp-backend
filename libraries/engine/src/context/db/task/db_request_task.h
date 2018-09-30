/**
 * @file db_request_task.h
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#ifndef ENGINE_DB_REQUEST_TASK_H
#define ENGINE_DB_REQUEST_TASK_H

#include "task/basic_task.h"

namespace engine {

    class db_request_task : public stl::crucial<basic_task, db_request_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(db_request_task)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(db_request_task)

        explicit db_request_task(nullptr_t) noexcept {}
        virtual ~db_request_task() = default;

    private:

    };

}

#endif /* ENGINE_DB_REQUEST_TASK_H */
