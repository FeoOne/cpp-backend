/**
 * @file io_context.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include "io/io_context.h"

namespace engine {

    using namespace framework;

    /**
     * Public
     */

    io_context::io_context(const config_setting::sptr& config) :
            execution_context(nullptr, config)
//            _should_work { false },
//            _should_restart { false },
//            _is_stopped { true }
    {

    }

    // virtual
    io_context::~io_context()
    {

    }

//    void io_context::start() noexcept
//    {
//        do {
//            _should_work = true;
//            _should_restart = false;
//
//            // @todo initialization stuff
//
//            {
//                _is_stopped = false;
//
//                while (_should_work) {
//                    _run_once();
//                }
//
//                _is_stopped = true;
//            }
//        } while (_should_restart);
//    }
//
//    void io_context::stop() noexcept
//    {
//        _should_work = false;
//    }
//
//    void io_context::restart() noexcept
//    {
//        _should_restart = true;
//
//        stop();
//    }
//
//    bool io_context::stopped() const noexcept
//    {
//        return _is_stopped;
//    }

    /**
     * Private
     */

//    void io_context::_run_once() noexcept
//    {
//
//    }

}
