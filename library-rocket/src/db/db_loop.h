/**
 * @file db_loop.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ROCKET_DB_LOOP_H
#define ROCKET_DB_LOOP_H

#include <uv.h>

#include "work/work_loop.h"

namespace rocket {

    class db_loop : public work_loop {
    public:
        GR_DECLARE_SMARTPOINTERS(db_loop)
        GR_DELETE_ALL_DEFAULT(db_loop)

        explicit db_loop(const task_queue::sptr& queue, task_handler *handler) noexcept;
        virtual ~db_loop();

        void start() noexcept final;
        void stop() noexcept final;

    private:
        uv_loop_t       _loop;
        uv_async_t      _async_handle;

        void on_async() noexcept;

        static void async_routine(uv_async_t *handle) noexcept;

    };

}

#endif /* ROCKET_DB_LOOP_H */
