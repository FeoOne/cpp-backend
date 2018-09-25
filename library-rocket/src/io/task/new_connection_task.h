/**
 * @file new_connection_task.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ROCKET_NEW_CONNECTION_TASK_H
#define ROCKET_NEW_CONNECTION_TASK_H

#include "task/basic_task.h"


namespace rocket {

    class new_connection_task : public groot::crucial<basic_task, new_connection_task> {
    public:
        GR_DECLARE_SMARTPOINTERS(new_connection_task)
        GR_DELETE_ALL_DEFAULT(new_connection_task)

        explicit new_connection_task(nullptr_t) noexcept {}
        virtual ~new_connection_task() = default;



    private:


    };

}

#endif /* ROCKET_NEW_CONNECTION_TASK_H */
