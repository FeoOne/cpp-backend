/**
 * @file timer.cpp
 * @author Feo
 * @date 30/09/2018
 * @brief
 */

#include "context/io/net/timer.h"

namespace rocket {

    void timer::setup(uv_loop_t *loop, u64 delay, u64 repeat, callback&& cb) noexcept
    {
        auto status { uv_timer_init(loop, &_timer.timer) };
        if (status!= 0) {
            logerror("Failed to init timer.");
        }
        uv_handle_set_data(&_timer.handle, this);

        _delay = delay;
        _repeat = repeat;
        _callback = std::move(cb);
    }

    void timer::start() noexcept
    {
        auto status { uv_timer_start(&_timer.timer, &timer::fire_callback, _delay, _repeat) };
        if (status!= 0) {
            logerror("Failed to start timer.");
        }
    }

    void timer::stop() noexcept
    {
        auto status { uv_timer_stop(&_timer.timer) };
        if (status!= 0) {
            logerror("Failed to stop timer.");
        }
    }

    void timer::on_fire() noexcept
    {
        _callback(this);
    }

    // static
    void timer::fire_callback(uv_timer_t *handle) noexcept
    {
        auto th { reinterpret_cast<timer_handle *>(handle) };
        if (th != nullptr) {
            auto data { uv_handle_get_data(&th->handle) };
            if (data != nullptr) {
                reinterpret_cast<timer *>(data)->on_fire();
            }
        }
    }

}
