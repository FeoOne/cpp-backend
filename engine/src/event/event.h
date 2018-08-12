/**
 * @file event.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_EVENT_H
#define ENGINE_EVENT_H

#include <framework.h>

namespace engine {

    class event {
    public:
        FW_DECLARE_SMARTPOINTERS(event)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(event)
        FW_CRUCIAL_BASE_DEFINITION()

        event();
        virtual ~event();

    private:

    };

}

#endif /* ENGINE_EVENT_H */
