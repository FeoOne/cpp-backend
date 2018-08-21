//
// Created by Feo on 16/08/2018.
//

#ifndef ROCKET_TASK_H
#define ROCKET_TASK_H

#include <groot.h>

namespace rocket {

    class task {
    public:
        FW_DECLARE_SMARTPOINTERS(task)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(task)
        FW_CRUCIAL_BASE_DEFINITION()

        virtual ~task() = default;

    protected:
        task() = default;

    };

}

#endif /* ROCKET_TASK_H */
