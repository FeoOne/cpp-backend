/**
 * @file execution_context.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include <events/context_did_start_event.h>
#include "core/execution_context.h"

namespace engine {

    using namespace framework;

    execution_context::execution_context(execution_loop::uptr&& loop,
                                         const event_queue::sptr& queue,
                                         const event_recipient::sptr& recipient,
                                         const config_setting::sptr& config) noexcept :
            _thread {},
            _loop { std::move(loop) },
            _should_restart { false },
            _queue { queue },
            _recipient { recipient },
            _config { config }
    {
        assert(config != nullptr);
    }

//    execution_context::~execution_context()
//    {
//    }

    void execution_context::start() noexcept
    {
        if (!_loop->stopped()) {
            logerror("Execution context already started.");
            return;
        }

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

    std::string_view execution_context::name() const noexcept
    {
        return { (*_config)["name"]->to_string() };
    }

    void execution_context::add_service(const execution_service::sptr &service) noexcept
    {
        _services.insert({ service->get_key(), service });
    }

    void execution_context::remove_service(execution_service::key_type key) noexcept
    {
        _services.erase(key);
    }

    execution_service::sptr execution_context::get_service(execution_service::key_type key) noexcept
    {
        return _services[key];
    }

    void execution_context::_execute() noexcept
    {
        do {
            if (_should_restart) {
                loginfo("Restarting context...");
                _should_restart = false;
            }

            before_run();
            _notify_about_start();
            _loop->run();
            after_run();
        } while (_should_restart);
    }

    void execution_context::_notify_about_start() noexcept
    {
        auto e = context_did_start_event::make_shared(shared_from_this());
        get_recipient()->enqueue(e);
    }

}
