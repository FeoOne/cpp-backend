/**
 * @file execution_context.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ROCKET_EXECUTION_CONTEXT_H
#define ROCKET_EXECUTION_CONTEXT_H

#if __APPLE__
#include <pthread/pthread.h>
#else
#include <pthread.h>
#endif

#include <groot.h>

#include "work/work_context.h"

namespace rocket {

    /**
     *
     */
    class worker final {
    public:
        GR_DECLARE_SMARTPOINTERS(worker)
        GR_DELETE_ALL_DEFAULT(worker)

        enum class detach_state {
            JOINABLE,
            DETACHED,
        };

        explicit worker(const groot::config_setting::sptr& config, work_context::uptr&& context) noexcept;
        ~worker();

        void start(detach_state state) noexcept;
        void stop() noexcept;

        void restart() noexcept;

        void join() noexcept;

    private:
        friend class worker_pool;

        pthread_t                           _thread;
        groot::config_setting::sptr         _config;
        work_context::uptr                  _context;
        bool                                _should_restart;

        void exec_routine() noexcept;

        static void *exec_routine(void *ptr) noexcept;

    };

}

#endif /* ROCKET_EXECUTION_CONTEXT_H */
