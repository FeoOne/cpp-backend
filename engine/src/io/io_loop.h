/**
 * @file io_loop.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_IO_LOOP_H
#define ENGINE_IO_LOOP_H

#include <uv.h>

#include "core/execution_loop.h"

namespace engine {

    class io_loop : public execution_loop {
    public:
        FW_DECLARE_SMARTPOINTERS(io_loop)
        FW_DELETE_ALL_DEFAULT(io_loop)

        explicit io_loop(const event_queue::sptr& queue) noexcept;
        virtual ~io_loop();

        void run() noexcept final;
        void stop() noexcept final;

        bool stopped() const noexcept final;

        void wakeup() noexcept final;

    private:
        std::unique_ptr<uv_loop_t>      _loop;
        std::unique_ptr<uv_async_t>     _async_handler;

        void notify_callback() noexcept;

        static void notify_callback(uv_async_t *handle) noexcept;

    };

}

#endif /* PROJECT_IO_LOOP_H */
