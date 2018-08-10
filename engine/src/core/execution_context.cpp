/**
 * @file execution_context.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include "core/execution_context.h"

namespace engine {

    execution_context::execution_context()
    {

    }

    execution_context::~execution_context()
    {
        shutdown();
        destroy();
    }

    void execution_context::notify_fork(fork_event_t event) noexcept
    {
        if (event == fork_event_t::PREPARE) {
            for (auto it = _services.rbegin(); it != _services.rend(); ++it) {
                it->notify_fork(event);
            }
        } else {
            for (auto it = _services.begin(); it != _services.end(); ++it) {
                it->notify_fork(event);
            }
        }
    }

    void execution_context::shutdown() noexcept
    {
        for (auto it = _services.rbegin(); it != _services.rend(); ++it) {
            it->shutdown();
        }
    }

    void execution_context::destroy() noexcept
    {
        for (auto it = _services.rbegin(); it != _services.rend(); ++it) {
            it->shutdown();
        }
    }

}
