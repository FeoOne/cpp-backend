/**
 * @file job_loop.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_JOB_LOOP_H
#define ENGINE_JOB_LOOP_H

#include "work/work_loop.h"
#include "event/event_queue.h"

namespace engine {

    class job_loop : public work_loop {
    public:
        FW_DECLARE_SMARTPOINTERS(job_loop)
        FW_DELETE_ALL_DEFAULT(job_loop)

        explicit job_loop(const event_queue::sptr& queue) noexcept;
        virtual ~job_loop() = default;

        void run() noexcept final;
        void stop() noexcept final;

        bool stopped() const noexcept final;

    private:
        std::atomic_bool            _is_stopped;
        std::atomic_bool            _should_work;

    };

}

#endif /* ENGINE_JOB_LOOP_H */
