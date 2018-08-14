/**
 * @file execution_loop.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTION_LOOP_H
#define ENGINE_EXECUTION_LOOP_H

#include "core/executor.h"
#include "event/event_queue.h"

namespace engine {

    class execution_loop {
    public:
        FW_DECLARE_SMARTPOINTERS(execution_loop)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(execution_loop)

        virtual ~execution_loop() = default;

        virtual void run() noexcept = 0;
        virtual void stop() noexcept = 0;

        virtual bool stopped() const noexcept = 0;

    protected:
        explicit execution_loop(const event_queue::sptr& queue) noexcept : _queue { queue } {}

        event_queue::sptr queue() const noexcept { return _queue; }

        void add_route(event::key_type key, const executor::sptr& exec) noexcept;
        void handle_event(const event::sptr& e) const noexcept;

    private:
        event_queue::sptr       _queue;

    };

}

#endif /* ENGINE_EXECUTION_LOOP_H */
