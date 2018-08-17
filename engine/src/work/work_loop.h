/**
 * @file execution_loop.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTION_LOOP_H
#define ENGINE_EXECUTION_LOOP_H

#include <framework.h>

namespace engine {

    class work_loop {
    public:
        FW_DECLARE_SMARTPOINTERS(work_loop)

        virtual ~work_loop() = default;

        virtual void start() noexcept = 0;
        virtual void stop() noexcept = 0;

    };

#if 0
    class work_loop {
    public:
        FW_DECLARE_SMARTPOINTERS(work_loop)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(work_loop)

        virtual ~work_loop() = default;

        virtual void run() noexcept = 0;
        virtual void stop() noexcept = 0;

        virtual bool stopped() const noexcept = 0;

        virtual void wakeup() noexcept;

        void register_event_handler(event::key_type key, const event_handler::sptr& handler) noexcept;

    protected:
        explicit work_loop(const event_queue::sptr& queue) noexcept : _queue { queue } {}

        event_queue::sptr get_queue() const noexcept { return _queue; }

        void handle_event(const event::sptr& e) const noexcept;

    private:
        using event_handler_map = std::unordered_map<event::key_type, event_handler::sptr>;

        event_queue::sptr       _queue;
        event_handler_map       _handlers;

    };
#endif

}

#endif /* ENGINE_EXECUTION_LOOP_H */
