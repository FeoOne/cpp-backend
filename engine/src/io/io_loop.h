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

    class io_loop : public work_loop {
    public:
        FW_DECLARE_SMARTPOINTERS(io_loop)
        FW_DELETE_ALL_DEFAULT(io_loop)

        explicit io_loop(const task_queue::sptr& queue, task_handler *handler) noexcept;
        virtual ~io_loop();

        void start() noexcept final;
        void stop() noexcept final;

    private:


    };

}

#endif /* PROJECT_IO_LOOP_H */
