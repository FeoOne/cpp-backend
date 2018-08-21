/**
 * @file worker_pool.cpp
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#include "system/system_context.h"

#include "worker_pool.h"

namespace rocket {

    worker_pool::worker_pool()
    {
    }

    void worker_pool::push(worker::uptr&& worker) noexcept
    {
        _workers[worker->_context->get_key()].push_back(std::move(worker));
    }

    void worker_pool::start() noexcept
    {
        for (size_t i = 0; i < _workers.size(); ++i) {
            auto& workers = _workers[i];
            auto state = (i == system_context::key()) ?
                         worker::detach_state::JOINABLE :
                         worker::detach_state::DETACHED;
            for (auto& worker: workers) {
                worker->start(state);
            }
        }
    }

}
