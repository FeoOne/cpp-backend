//
// Created by Feo on 16/08/2018.
//

#ifndef ROCKET_TASK_H
#define ROCKET_TASK_H

#include <groot.h>

#include "main/rocket_consts.h"

namespace rocket {

    class task {
    public:
        GR_DECLARE_SMARTPOINTERS(task)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(task)
        GR_CRUCIAL_BASE_DEFINITION(RC_TASK_TYPE_MAX_KEY_COUNT)

        virtual ~task() = default;

    protected:
        task() = default;

    };

}

#endif /* ROCKET_TASK_H */
