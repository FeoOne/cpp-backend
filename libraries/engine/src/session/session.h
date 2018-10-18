/**
 * @file session.h
 * @author Feo
 * @date 17/10/2018
 * @brief
 */

#ifndef ENGINE_SESSION_H
#define ENGINE_SESSION_H

#include <stl.h>

namespace engine {

    class session {
    public:
        STL_DECLARE_SMARTPOINTERS(session)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(session)

        session() = default;
        virtual ~session() = default;

    private:

    };

}

#endif /* ENGINE_SESSION_H */
