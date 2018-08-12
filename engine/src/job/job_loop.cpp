/**
 * @file job_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "job/job_loop.h"

namespace engine {

    using namespace std::chrono_literals;

    job_loop::job_loop() :
            _is_stopped { true },
            _should_work { false }
    {

    }

    // virtual
    job_loop::~job_loop()
    {
    }

    // virtual
    void job_loop::run() noexcept
    {
        _should_work = true;
        _is_stopped = false;
        while (_should_work) {
            std::this_thread::sleep_for(1s);
        }
        _is_stopped = true;
    }

    // virtual
    void job_loop::stop() noexcept
    {
        _should_work = false;
    }

    // virtual
    bool job_loop::stopped() const noexcept
    {
        return _is_stopped;
    }

}
