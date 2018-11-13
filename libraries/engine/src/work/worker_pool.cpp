/**
 * @file worker_pool.cpp
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#include "context/system/system_context.h"

#include "worker_pool.h"

namespace engine {

    worker_pool::worker_pool() :
            _workers {}
    {
    }

    void worker_pool::push(worker::uptr&& worker) noexcept
    {
        _workers[worker->get_context_key()] = std::move(worker);
    }

    void worker_pool::start() noexcept
    {
        for (size_t i = 0; i < _workers.size(); ++i) {
            auto worker { _workers[i].get() };
            if (worker == nullptr) {
                continue;
            }

            auto state { worker::detach_state::DETACHED };
            if (i == system_context::key()) {
                state = worker::detach_state::JOINABLE;
            }

            worker->start(state);
        }
    }

}
