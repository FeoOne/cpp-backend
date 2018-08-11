/**
 * @file execution_loop.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTION_LOOP_H
#define ENGINE_EXECUTION_LOOP_H

#include <framework.h>

namespace engine {

    class execution_loop {
    public:
        FW_DECLARE_SMARTPOINTERS(execution_loop)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(execution_loop)

        virtual ~execution_loop() = default;

        virtual void run() noexcept = 0;
        virtual void stop() noexcept = 0;

        virtual bool stopped() const noexcept = 0;

    protected:
        execution_loop() = default;

    };

}

#endif /* PROJECT_EXECUTION_LOOP_H */
