//
// Created by Feo on 30/10/2018.
//

#include "work/service/event_center.h"

namespace engine {

    /**
     * event_binding
     */

    event_binding::event_binding(event_stream *stream) noexcept :
            _stream { stream }
    {
    }

    event_binding::~event_binding()
    {
        _stream->unbind(this);
    }

}
