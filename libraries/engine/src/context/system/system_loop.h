/**
 * @file system_loop.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_SYSTEM_LOOP_H
#define ENGINE_SYSTEM_LOOP_H

#include "work/work_loop.h"

namespace engine {

    class system_loop : public work_loop {
    public:
        STL_DECLARE_SMARTPOINTERS(system_loop)
        STL_DELETE_ALL_DEFAULT(system_loop)

        explicit system_loop(task_queue *queue, const task_handler *handler) noexcept;
        virtual ~system_loop();

        void start() noexcept final;
        void stop() noexcept final;

    private:
        bool                _should_work; // todo: mt safety

    };

}

#endif /* ENGINE_SYSTEM_LOOP_H */
