/**
 * @file io_context.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ENGINE_IO_CONTEXT_H
#define ENGINE_IO_CONTEXT_H

#include "core/execution_context.h"

namespace engine {

    /**
     * @todo implement `run_for` and `run_until` methods
     */
    class io_context : public execution_context {
    public:
        io_context();
        virtual ~io_context();

        void start() noexcept;
        void stop() noexcept;
        void restart() noexcept;
        bool stopped() const noexcept;

        FW_DELETE_DEFAULT_COPY_CTOR(io_context)
        FW_DELETE_DEFAULT_COPY_ASSIGN(io_context)

    private:
        std::atomic_bool            _should_work;
        std::atomic_bool            _should_restart;
        std::atomic_bool            _is_stopped;

        void _run_once() noexcept;

    };

}

#endif /* ENGINE_IO_CONTEXT_H */
