/**
 * @file worker_pool.h
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#ifndef ENGINE_WORKER_POOL_H
#define ENGINE_WORKER_POOL_H

#include "work/worker.h"

namespace engine {

    class worker_pool {
    public:
        FW_DECLARE_SMARTPOINTERS(worker_pool)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(worker_pool)

        worker_pool() = default;
        ~worker_pool() = default;

        void push(worker::uptr&& worker) noexcept;

    private:
        std::vector<worker::uptr>       _workers;

    };

}

#endif /* ENGINE_WORKER_POOL_H */
