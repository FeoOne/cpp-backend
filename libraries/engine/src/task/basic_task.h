//
// Created by Feo on 16/08/2018.
//

#ifndef ENGINE_TASK_H
#define ENGINE_TASK_H

#include <stl.h>

#include "main/engine_consts.h"

namespace engine {

    /**
     * Base task class.
     */
    class basic_task {
    public:
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(basic_task)
        STL_CRUCIAL_BASE_DEFINITION(EX_TASK_TYPE_MAX_KEY_COUNT)
        STL_DECLARE_NEW_DELETE(basic_task)

        virtual ~basic_task() = default;

    protected:
        basic_task() = default;

    };

}

#endif /* ENGINE_TASK_H */
