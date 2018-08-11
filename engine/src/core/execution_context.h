/**
 * @file execution_context.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTION_CONTEXT_H
#define ENGINE_EXECUTION_CONTEXT_H

#include <framework.h>

#include "core/execution_loop.h"

namespace engine {

    class execution_context {
    public:
        FW_DECLARE_SMARTPOINTERS(execution_context)
        FW_DELETE_ALL_DEFAULT(execution_context)

        virtual ~execution_context();

        void start() noexcept;
        void stop() noexcept;
        void restart() noexcept;

        void join() noexcept;

    protected:
        explicit execution_context(execution_loop::uptr&& loop,
                                   const framework::config_setting::sptr& config) noexcept;

        framework::config_setting::sptr& config() noexcept { return _config; }

        virtual void _before_run() noexcept = 0;
        virtual void _after_run() noexcept = 0;

    private:
        execution_loop::uptr                _loop;
        framework::config_setting::sptr     _config;
        std::thread                         _thread;
        bool                                _should_restart;

        void _execute() noexcept;

    };

}

#endif /* ENGINE_EXECUTION_CONTEXT_H */
