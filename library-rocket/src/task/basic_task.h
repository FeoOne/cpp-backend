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

        virtual ~basic_task() = default;

        template<typename T, typename... Args>
        static T *create(Args&&... args) noexcept {
            return new (groot::memory::malloc<void>(sizeof(T))) T(std::forward<Args>(args)...);
        }

        static void destroy(basic_task *any_task) noexcept {
            any_task->~basic_task();
            groot::memory::free(any_task);
        }

    protected:
        basic_task() = default;

    };

}

#endif /* ROCKET_TASK_H */
