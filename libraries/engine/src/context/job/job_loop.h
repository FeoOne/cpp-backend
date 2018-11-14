/**
 * @file job_loop.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_JOB_LOOP_H
#define ENGINE_JOB_LOOP_H

#include <uv.h>

#include "work/work_loop.h"

namespace engine {

    class job_loop : public work_loop {
    public:
        STL_DECLARE_SMARTPOINTERS(job_loop)
        STL_DELETE_ALL_DEFAULT(job_loop)

        explicit job_loop(task_queue *queue, const task_handler *handler) noexcept;
        virtual ~job_loop();

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

#endif /* ENGINE_JOB_LOOP_H */
