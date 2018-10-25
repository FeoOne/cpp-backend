/**
 * @file db_loop.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ENGINE_DB_LOOP_H
#define ENGINE_DB_LOOP_H

#include <uv.h>

#include "work/work_loop.h"

namespace engine {

    class db_loop : public work_loop {
    public:
        STL_DECLARE_SMARTPOINTERS(db_loop)
        STL_DELETE_ALL_DEFAULT(db_loop)

        explicit db_loop(task_queue *queue, const task_handler *handler) noexcept;
        virtual ~db_loop();

        void start() noexcept final;
        void stop() noexcept final;

        uv_loop_t *get_loop() noexcept { return &_loop; }

    private:
        uv_loop_t           _loop;
        uv_async_t          _async_handle;

        void notify() noexcept;
        void on_async() noexcept;

        static void async_callback(uv_async_t *handle) noexcept;

    };

}

#endif /* ENGINE_DB_LOOP_H */
