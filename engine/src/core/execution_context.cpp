/**
 * @file execution_context.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include "core/execution_context.h"

namespace engine {

    using namespace framework;

    execution_context::execution_context(execution_loop::uptr&& loop,
                                         const event_queue::sptr& queue,
                                         const config_setting::sptr& config) noexcept :
            _loop { std::move(loop) },
            _queue { queue },
            _config { config },
            _thread {},
            _should_restart { false }
    {
        assert(config != nullptr);
    }

    execution_context::~execution_context()
    {
    }

    void execution_context::start() noexcept
    {
        if (!_loop->stopped()) {
            logerror("Execution context already started.");
            return;
        }

        loginfo("Starting execution context thread.");

        _thread = std::thread(std::bind(&execution_context::_execute, this));
    }

    void execution_context::stop() noexcept
    {
        if (_loop->stopped()) {
            logerror("Execution context already stopped.");
            return;
        }

        _loop->stop();
    }

    void execution_context::restart() noexcept
    {
        if (_loop->stopped()) {
            logerror("Can't restart stopped context.");
            return;
        }

        _should_restart = true;

        stop();
    }

    void execution_context::join() noexcept
    {
        if (_thread.joinable()) {
            _thread.join();
        } else {
            logerror("Can't join thread.");
        }
    }

    void execution_context::_add_service(const execution_service::sptr& service) noexcept
    {
        _services.insert({ service->get_key(), service }); // @todo Error handling
    }

    void execution_context::_remove_service(execution_service::key_type key) noexcept
    {
        _services.erase(key); // @todo Error handling
    }

    execution_service::sptr execution_context::_get_service(execution_service::key_type key) noexcept
    {
        return _services[key]; // @todo Error handling
    }

    void execution_context::_execute() noexcept
    {
        do {
            if (_should_restart) {
                loginfo("Restarting context...");
                _should_restart = false;
            }

            _before_run();
            _loop->run();
            _after_run();
        } while (_should_restart);
    }

}
