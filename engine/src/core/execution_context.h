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
        FW_DELETE_ALL_DEFAULT(execution_context)

        virtual ~execution_context();

        void start() noexcept;
        void stop() noexcept;
        void restart() noexcept;
        void join() noexcept;

        bool stopped() const noexcept;

    protected:
        explicit execution_context(const framework::config_setting::sptr& config) noexcept;

        framework::config_setting::sptr& config() noexcept { return _config; }

        virtual void _poll_once() noexcept = 0;

        virtual void _before_execute() noexcept = 0;
        virtual void _after_execute() noexcept = 0;

        virtual bool _should_work() const noexcept = 0;
        virtual void _should_work(bool b) noexcept = 0;

    private:
        std::vector<execution_service>      _services;

        framework::config_setting::sptr     _config;

        std::atomic_bool                    _should_restart;
        std::atomic_bool                    _is_stopped;

        std::thread                         _thread;

        void _execute() noexcept;

    };

}

#endif /* ENGINE_EXECUTION_CONTEXT_H */
