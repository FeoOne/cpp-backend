/**
 * @file timer.h
 * @author Feo
 * @date 30/09/2018
 * @brief
 */

#ifndef ROCKET_TIMER_H
#define ROCKET_TIMER_H

#include <groot.h>

#include "context/io/net/network.h"

namespace rocket {

    class timer final {
    public:
        GR_DECLARE_SMARTPOINTERS(timer)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(timer)

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

#endif /* ROCKET_TIMER_H */
