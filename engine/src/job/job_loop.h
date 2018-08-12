/**
 * @file job_loop.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_JOB_LOOP_H
#define ENGINE_JOB_LOOP_H

#include "core/execution_loop.h"
#include "event/event_queue.h"

namespace engine {

    class job_loop : public execution_loop {
    public:
        FW_DECLARE_SMARTPOINTERS(job_loop)
        FW_DELETE_ALL_DEFAULT(job_loop)

        job_loop(const event_queue::sptr& queue);
        virtual ~job_loop();

        void run() noexcept final;
        void stop() noexcept final;

        bool stopped() const noexcept final;

    private:
        std::atomic_bool            _is_stopped;
        std::atomic_bool            _should_work;

        event_queue::sptr           _queue;

    };

}

#endif /* ENGINE_JOB_LOOP_H */
