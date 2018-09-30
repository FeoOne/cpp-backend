/**
 * @file timer.h
 * @author Feo
 * @date 30/09/2018
 * @brief
 */

#ifndef ENGINE_TIMER_H
#define ENGINE_TIMER_H

#include <stl.h>

#include "context/io/net/network.h"

namespace engine {

    class timer final {
    public:
        STL_DECLARE_SMARTPOINTERS(timer)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(timer)

        using callback = std::function<void(timer *)>;

        timer() : _timer {} {}
        ~timer() = default;

        void setup(uv_loop_t *loop, u64 delay, u64 repeat, callback&& cb) noexcept;

        void start() noexcept;
        void stop() noexcept;

    private:
        timer_handle        _timer;
        u64                 _delay;
        u64                 _repeat;
        callback            _callback;

        void on_fire() noexcept;

        static void fire_callback(uv_timer_t *handle) noexcept;

    };

}

#endif /* ENGINE_TIMER_H */
