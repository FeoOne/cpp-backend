/**
 * @file worker_pool.h
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#ifndef ENGINE_WORKER_POOL_H
#define ENGINE_WORKER_POOL_H

#include "work/worker.h"
#include "main/engine_consts.h"

namespace engine {

    /**
     * This class is a container which store workers and provide access.
     */
    class worker_pool final {
    public:
        STL_DECLARE_SMARTPOINTERS(worker_pool)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(worker_pool)

        worker_pool();
        ~worker_pool() = default;

        void push(worker::uptr&& worker) noexcept;

        void start() noexcept;

        template<typename Context>
        inline worker *get_worker() noexcept {
            return _workers[Context::key()].get();
        }

    private:
        std::array<worker::uptr, EX_WORK_CONTEXT_TYPE_MAX_KEY_COUNT>    _workers;

    };

}

#endif /* ENGINE_WORKER_POOL_H */
