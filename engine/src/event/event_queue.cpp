/**
 * @file event_queue.cpp
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#include "event/event_queue.h"

namespace engine {

    void event_queue::push(const event::sptr& e) noexcept
    {
        _queue.push(e);
    }

    event::sptr event_queue::pop() noexcept
    {
        auto e = _queue.front();
        _queue.pop();
        return e;
    }

}
