/**
 * @file execution_context.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTION_CONTEXT_H
#define ENGINE_EXECUTION_CONTEXT_H

#include <framework.h>

#include "execution_service.h"

namespace engine {

    class execution_context {
    public:
        FW_DECLARE_SMARTPOINTERS(execution_context)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(execution_context)

        virtual ~execution_context();

        void start() noexcept;
        void stop() noexcept;
        void restart() noexcept;
        void join() noexcept;

        bool stopped() const noexcept;

    protected:
        execution_context();

    private:
        std::vector<execution_service>      _services;

        std::atomic_bool                    _should_work;
        std::atomic_bool                    _should_restart;
        std::atomic_bool                    _is_stopped;

        std::thread                         _thread;

        void execute() noexcept;

    };

}

#endif /* ENGINE_EXECUTION_CONTEXT_H */
