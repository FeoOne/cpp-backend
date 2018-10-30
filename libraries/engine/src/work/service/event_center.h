//
// Created by Feo on 30/10/2018.
//

#ifndef ENGINE_EVENT_CENTER_H
#define ENGINE_EVENT_CENTER_H

#include <stl.h>

namespace engine {

    class event_observer {
    public:

    private:
        std::function<void(void)>       _callback;

    };

    class event_center {
    public:

    private:

    };

}

#endif /* ENGINE_EVENT_CENTER_H */
