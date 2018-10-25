/**
 * @file io_loop.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_IO_LOOP_H
#define ENGINE_IO_LOOP_H

#include <uv.h>

#include "work/work_loop.h"

namespace engine {

    class io_loop final : public work_loop {
    public:
        STL_DECLARE_SMARTPOINTERS(io_loop)
        STL_DELETE_ALL_DEFAULT(io_loop)

        explicit io_loop(task_queue *queue, const task_handler *handler) noexcept;
        virtual ~io_loop();

        void start() noexcept final;
        void stop() noexcept final;

        uv_loop_t *loop() noexcept { return &_loop; }

    private:
        uv_loop_t       _loop;
        uv_async_t      _async_handle;

        void notify() noexcept;
        void on_async() noexcept;

        static void async_callback(uv_async_t *handle) noexcept;

    };

}

#endif /* PROJECT_IO_LOOP_H */
