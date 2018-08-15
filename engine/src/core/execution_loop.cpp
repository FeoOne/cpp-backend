/**
 * @file execution_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "events/events.h"

#include "core/execution_loop.h"

namespace engine {

    void execution_loop::handle_event(const event::sptr& eve) const noexcept
    {
        auto it = _handlers.find(eve->get_key());
        if (it != _handlers.end()) {
            (*it->second)(eve);
        }
    }

    void execution_loop::register_event_handler(event::key_type key, const event_handler::sptr& handler) noexcept
    {
        auto it = _handlers.find(key);
        if (it == _handlers.end()) {
            _handlers.insert({ key, handler });
        } else {
            logerror("Handler for key %lu '%s' already exists.", key, event_name_from_key(key).data());
        }
    }

}
