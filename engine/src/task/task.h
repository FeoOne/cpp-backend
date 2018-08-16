//
// Created by Feo on 16/08/2018.
//

#ifndef ENGINE_TASK_H
#define ENGINE_TASK_H

#include <framework.h>

namespace engine {

    class task {
    public:
        FW_DECLARE_SMARTPOINTERS(task)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(task)
        FW_CRUCIAL_BASE_DEFINITION()

        task() = default;
        virtual ~task() = default;

    };

}

#endif /* ENGINE_TASK_H */
