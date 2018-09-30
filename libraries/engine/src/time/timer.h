/**
 * @file timer.h
 * @author Feo
 * @date 15/09/2018
 * @brief
 */

#ifndef ENGINE_TIMER_H
#define ENGINE_TIMER_H

#include <stl.h>

namespace engine {

    class timer {
    public:
        STL_DECLARE_SMARTPOINTERS(timer)
        STL_DELETE_ALL_DEFAULT(timer)

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

#endif /* ENGINE_TIMER_H */
