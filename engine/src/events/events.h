/**
 * @file events.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_EVENTS_H
#define ENGINE_EVENTS_H

#include "events/context_did_start_event.h"

namespace engine {

    /**
     * @brief Used for debug output.
     * @param key Event key.
     * @return Event name.
     */
    const std::string_view& event_name_from_key(event::key_type key) noexcept;

}

#endif /* ENGINE_EVENTS_H */
