/**
 * @file execution_context.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTION_CONTEXT_H
#define ENGINE_EXECUTION_CONTEXT_H

#ifdef STL_PLATFORM_APPLE
#include <pthread/pthread.h>
#else
#include <pthread.h>
#endif

#include <stl.h>

#include "work/work_context.h"

namespace engine {

    /**
     *
     */
    class worker final {
    public:
        STL_DECLARE_SMARTPOINTERS(worker)
        STL_DELETE_ALL_DEFAULT(worker)

        enum class detach_state {
            JOINABLE,
            DETACHED,
        };

        explicit worker(const stl::setting& config, work_context::uptr&& context) noexcept;
        ~worker() = default;

        void start(detach_state state) noexcept;
        void stop() noexcept;

        void restart() noexcept;

        void join() noexcept;

        work_context::key_type get_context_key() const noexcept { return _context->get_key(); }

    private:
        pthread_t                       _thread;
        const stl::setting              _config;
        work_context::uptr              _context;
        bool                            _should_restart;

        void exec_callback() noexcept;

        static void *exec_callback(void *ptr) noexcept;

    };

}

#endif /* ENGINE_EXECUTION_CONTEXT_H */
