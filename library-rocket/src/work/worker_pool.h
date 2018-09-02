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

    /**
     * This class is a container which store workers and provide access.
     */
    class worker_pool final {
    public:
        GR_DECLARE_SMARTPOINTERS(worker_pool)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(worker_pool)

        worker_pool();
        ~worker_pool() = default;

        void push(worker::uptr&& worker) noexcept;

        void start() noexcept;

        template<typename Context>
        const worker::uptr& get_worker() noexcept {
            return _workers[Context::key()][0].get();
        }

        template<typename Context>
        std::vector<worker::uptr>& get_workers() noexcept {
            return _workers[Context::key()];
        }

    private:
        std::array<std::vector<worker::uptr>, consts::WORK_CONTEXT_TYPE_MAX_KEY>    _workers;

    };

}

#endif /* ROCKET_WORKER_POOL_H */
