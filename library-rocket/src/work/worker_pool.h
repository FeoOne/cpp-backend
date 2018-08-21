/**
 * @file worker_pool.h
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#ifndef ROCKET_WORKER_POOL_H
#define ROCKET_WORKER_POOL_H

#include "work/worker.h"
#include "main/rocket_consts.h"

namespace rocket {

    class worker_pool {
    public:
        FW_DECLARE_SMARTPOINTERS(worker_pool)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(worker_pool)

        worker_pool();
        ~worker_pool() = default;

        void push(worker::uptr&& worker) noexcept;

        void start() noexcept;

        template<typename Context>
        worker::uptr& get_worker() noexcept {
            return _workers[Context::key()][0];
        }

    private:
        std::array<std::vector<worker::uptr>, consts::WORK_CONTEXT_TYPE_MAX_COUNT>    _workers;

    };

}

#endif /* ROCKET_WORKER_POOL_H */
