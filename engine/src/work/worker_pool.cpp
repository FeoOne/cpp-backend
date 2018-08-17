/**
 * @file worker_pool.cpp
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#include "worker_pool.h"

namespace engine {

    void worker_pool::push(worker::uptr&& worker) noexcept
    {
        _workers[worker->_context->get_key()].push_back(std::move(worker));
    }

}
