/**
 * @file events.cpp
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#include "events/events.h"

namespace engine {

    const std::string_view& event_name_from_key(event::key_type key) noexcept
    {
        static std::unordered_map<event::key_type, std::string_view> names {
            { context_did_start_event::key(), "context_did_start_event" }
        };
        return names[key];
    }

}
