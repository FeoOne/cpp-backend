//
// Created by Feo on 16/08/2018.
//

#ifndef ROCKET_TASK_H
#define ROCKET_TASK_H

#include <groot.h>

#include "main/rocket_consts.h"

namespace rocket {

    /**
     * Base task class.
     */
    class basic_task {
    public:
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(basic_task)
        GR_CRUCIAL_BASE_DEFINITION(RC_TASK_TYPE_MAX_KEY_COUNT)

        virtual ~basic_task() = 0;

        template<typename T, typename... Args>
        static T *create(Args&&... args) noexcept {
            return new (je_malloc(sizeof(T))) T(std::forward<Args>(args)...);
        }

        template<typename T>
        static void destroy(T *any_task) noexcept {
            any_task->~T();
            je_free(any_task);
        }

    protected:
        basic_task() = default;

    };

}

#endif /* ROCKET_TASK_H */
