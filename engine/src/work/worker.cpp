/**
 * @file execution_context.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include <events/context_did_start_event.h>
#include "work/worker.h"

namespace engine {

    using namespace framework;

    worker::worker(const config_setting::sptr& config, work_context::uptr&& context) noexcept :
            _thread { nullptr },
            _config { config },
            _context { std::move(context) },
            _should_restart { false }
    {
    }

    // virtual
    worker::~worker()
    {
    }

    void worker::start(detach_state state) noexcept
    {
        static const std::unordered_map<detach_state, int> POSIX_DETACH_STATE {
                { detach_state::JOINABLE, PTHREAD_CREATE_JOINABLE },
                { detach_state::DETACHED, PTHREAD_CREATE_DETACHED },
        };

        int status;
        pthread_attr_t attributes;

        status = pthread_attr_init(&attributes);
        logassert(status == 0);
        status = pthread_attr_setdetachstate(&attributes, POSIX_DETACH_STATE.at(state));
        logassert(status == 0);
        status = pthread_attr_setscope(&attributes, PTHREAD_SCOPE_PROCESS); // make thread unbound
        logassert(status == 0);
        status = pthread_create(&_thread, &attributes, &worker::exec_routine, this);
        logassert(status == 0);
    }

    void worker::stop() noexcept
    {
        _should_restart = false;
        _context->stop();
    }

    void worker::restart() noexcept
    {
        _should_restart = true;
        _context->stop();
    }

    void worker::join() noexcept
    {
        int status = pthread_join(_thread, nullptr);
        logassert(status == 0);
    }

    void worker::exec_routine() noexcept
    {
        do {
            _context->start();
        } while (_should_restart);
    }

    // static
    void *worker::exec_routine(void *ptr) noexcept
    {
        (reinterpret_cast<worker *>(ptr))->exec_routine();
        pthread_exit(nullptr);
    }




#if 0
    worker::worker(work_loop::uptr&& loop,
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

    void worker::start() noexcept
    {
        if (!_loop->stopped()) {
            logerror("Execution context already started.");
            return;
        }

        _thread = std::thread(std::bind(&worker::_execute, this));
    }

    void worker::stop() noexcept
    {
        if (_loop->stopped()) {
            logerror("Execution context already stopped.");
            return;
        }

        _loop->stop();
    }

    void worker::restart() noexcept
    {
        if (_loop->stopped()) {
            logerror("Can't restart stopped context.");
            return;
        }

        _should_restart = true;

        stop();
    }

    void worker::join() noexcept
    {
        if (_thread.joinable()) {
            _thread.join();
        } else {
            logerror("Can't join thread.");
        }
    }

    std::string_view worker::name() const noexcept
    {
        return { (*_config)["name"]->to_string() };
    }

    void worker::add_service(const work_service::sptr &service) noexcept
    {
        _services.insert({ service->get_key(), service });
    }

    void worker::remove_service(work_service::key_type key) noexcept
    {
        _services.erase(key);
    }

    work_service::sptr worker::get_service(work_service::key_type key) noexcept
    {
        return _services[key];
    }

    void worker::_execute() noexcept
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

    void worker::_notify_about_start() noexcept
    {
        auto e = context_did_start_event::make_shared(shared_from_this());
        get_recipient()->enqueue(e);
    }
#endif

}
