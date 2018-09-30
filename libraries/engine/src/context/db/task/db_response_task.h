/**
 * @file db_response_task.h
 * @author Feo
 * @date 26/08/2018
 * @brief
 */

#ifndef ENGINE_DB_RESPONSE_TASK_H
#define ENGINE_DB_RESPONSE_TASK_H

#include "task/basic_task.h"

namespace engine {

    class db_response_task : public stl::crucial<basic_task, db_response_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(db_response_task)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(db_response_task)

        explicit db_response_task(nullptr_t) noexcept {}
        virtual ~db_response_task() = default;

    private:

    };

}

#endif /* ENGINE_DB_RESPONSE_TASK_H */
