//
// Created by Feo on 25/10/2018.
//

#ifndef ENGINE_WORK_SERVICE_COMMUNICATOR_H
#define ENGINE_WORK_SERVICE_COMMUNICATOR_H

#include <stl.h>

namespace engine {

    class basic_observer {
    public:
        STL_DECLARE_SMARTPOINTERS(basic_observer)
    };

    template<typename T, typename H>
    class observer {
    public:
        STL_DECLARE_SMARTPOINTERS(observer<T STL_COMMA() H>)
    };

    class basic_notification {
    public:
        STL_DECLARE_SMARTPOINTERS(basic_notification)
    };

}

#endif /* ENGINE_WORK_SERVICE_COMMUNICATOR_H */
