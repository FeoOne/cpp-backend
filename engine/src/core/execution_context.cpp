/**
 * @file execution_context.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include "core/execution_context.h"

namespace engine {

    using namespace framework;

    execution_context::execution_context(const config_setting::sptr& config) noexcept :
            _services {},
            _config { config },
            _should_restart { false },
            _is_stopped { true },
            _thread {}
    {
        assert(config != nullptr);
    }

    execution_context::~execution_context()
    {
    }

    void execution_context::start() noexcept
    {
        if (!stopped()) {
            logerror("Execution context already started.");
            return;
        }

        _thread = std::thread(std::bind(&execution_context::_execute, this));
    }

    void execution_context::stop() noexcept
    {
        if (!stopped()) {
            _should_work(false);
        } else {
            logerror("Execution context already stopped.");
        }
    }

    void execution_context::restart() noexcept
    {
        if (!stopped()) {
            _should_restart = true;
            stop();
        } else {
            start();
        }
    }

    void execution_context::join() noexcept
    {
        if (_thread.joinable()) {
            _thread.join();
        } else {
            logerror("Can't join thread.");
        }
    }

    bool execution_context::stopped() const noexcept
    {
        return _is_stopped;
    }

    void execution_context::_execute() noexcept
    {
        _is_stopped = false;

        do {
            if (_should_restart) {
                loginfo("Restarting context.");
                _should_restart = false;
            }

            _before_execute();

            do {
                _poll_once();
            } while (_should_work());

            _after_execute();
        } while (_should_restart);

        _is_stopped = true;
    }

}
