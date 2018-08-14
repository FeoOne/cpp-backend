/**
 * @file executor.h
 * @author Feo
 * @date 14/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTOR_H
#define ENGINE_EXECUTOR_H

#include "event/event.h"

namespace engine {

    class executor {
    public:
        FW_DECLARE_SMARTPOINTERS(executor)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(executor)

        virtual ~executor() = default;

        virtual std::vector<event::sptr> operator()(const event::sptr& e) noexcept = 0;

    protected:
        executor() = default;

    };

}

#endif /* ENGINE_EXECUTOR_H */
