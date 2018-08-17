/**
 * @file worker_pool.h
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#ifndef ENGINE_WORKER_POOL_H
#define ENGINE_WORKER_POOL_H

#include "work/worker.h"
#include "main/engine_const.h"

namespace engine {

    class worker_pool {
    public:
        FW_DECLARE_SMARTPOINTERS(worker_pool)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(worker_pool)

        worker_pool() = default;
        ~worker_pool() = default;

        void push(worker::uptr&& worker) noexcept;

    private:
        std::array<std::vector<worker::uptr>, engine_const::WORK_CONTEXT_TYPE_MAX_COUNT>    _workers;

    };

}

#endif /* ENGINE_WORKER_POOL_H */
