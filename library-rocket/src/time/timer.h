/**
 * @file timer.h
 * @author Feo
 * @date 15/09/2018
 * @brief
 */

#ifndef ROCKET_TIMER_H
#define ROCKET_TIMER_H

#include <groot.h>

namespace rocket {

    class timer {
    public:
        GR_DECLARE_SMARTPOINTERS(timer)
        GR_DELETE_ALL_DEFAULT(timer)

        virtual ~timer() = default;

    protected:
        explicit timer(std::chrono::milliseconds interval, bool need_repeat, std::function<void()>&& cb) noexcept :
                _interval { interval },
                _need_repeat { need_repeat },
                _cb { std::move(cb) }
        {}

        std::chrono::milliseconds interval() const noexcept { return _interval; }
        bool need_repeat() const noexcept { return _need_repeat; }

        void fire() const noexcept { _cb(); }

    private:
        std::chrono::milliseconds       _interval;
        bool                            _need_repeat;
        std::function<void()>           _cb;

    };

}

#endif /* ROCKET_TIMER_H */
