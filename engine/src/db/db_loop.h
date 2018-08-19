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
        FW_DECLARE_SMARTPOINTERS(db_loop)
        FW_DELETE_ALL_DEFAULT(db_loop)

        explicit db_loop(const task_queue::sptr& queue, task_handler *handler) noexcept;
        virtual ~db_loop();

        void start() noexcept final;
        void stop() noexcept final;

    private:


    };

}

#endif /* ENGINE_DB_LOOP_H */
